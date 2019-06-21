#include "apiclient.h"
#include "categorylist.h"
#include "category.h"

#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

ApiClient::ApiClient(QObject *parent): QObject(parent),
    networkManager(this)
{

    connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));
}

void ApiClient::getAllCategory(CategoryList *list) {
    QUrl url("https://api.thecatapi.com/v1/breeds");
    QNetworkRequest request;
    request.setUrl(url);

    categoryList = list;
    networkManager.get(request);
}

void ApiClient::onResult(QNetworkReply* reply){
    categoryList->clear();
    if(reply->error() != QNetworkReply::NoError)
        return;
    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);

    QJsonArray array = jsonResponse.array();

    for(const QJsonValue& value : array) {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        categoryList->createCategory(name);
    }
    emit finishedLoad();
    reply->deleteLater();
}
