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

CategoryList *ApiClient::getAllCategory() {
    QUrl url("https://api.thecatapi.com/v1/breeds");
    QNetworkRequest request;
    request.setUrl(url);

    networkManager.get(request);
}

void ApiClient::onResult(QNetworkReply* reply){
    if(reply->error() != QNetworkReply::NoError)
        return;
    CategoryList categoryList;
    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);

    QJsonArray array = jsonResponse.array();

    qDebug() << "zero: " << array[0];
    for(const QJsonValue& value : array) {
        QJsonObject obj = value.toObject();
        qDebug()<< "name: " << obj["name"];
        QString name = obj["name"].toString();
        Category category(name);
        categoryList.append(&category);
    }

    reply->deleteLater();
}
