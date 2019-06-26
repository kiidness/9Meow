#include "apiclient.h"
#include "categorylist.h"
#include "category.h"
#include "catimagelist.h"

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

void ApiClient::getAllImages(QString categoryName, CatImageList *list)
{
    QUrl url("https://api.thecatapi.com/v1/images/search?limit=20&breed_ids="+categoryName);
    QNetworkRequest request;
    request.setUrl(url);

    catImageList = list;
    networkManager.get(request);
}

void ApiClient::getAllVotes()
{
    QUrl url("https://api.thecatapi.com/v1/votes");
    QNetworkRequest request;
    request.setRawHeader("x-api-key","f84b184e-f7f8-4b6f-af11-e4569b2c44dbs");
    request.setUrl(url);
    networkManager.get(request);
}

void ApiClient::onResult(QNetworkReply* reply){
    if(reply->error() != QNetworkReply::NoError)
        return;
    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);

    QJsonArray array = jsonResponse.array();

    auto a = array[0].toObject();

    if(a["url"].toString() != ""){
        catImageList->clear();
        for(const QJsonValue& value : array) {
            QJsonObject obj = value.toObject();
            QString name = obj["id"].toString();
            QString url = obj["url"].toString();
            catImageList->createCatImage(name, url);
        }
        emit finishedLoadCatImages();
    }
    else{
        categoryList->clear();
        for(const QJsonValue& value : array) {
            QJsonObject obj = value.toObject();
            QString name = obj["name"].toString();
            QString id = obj["id"].toString();
            categoryList->createCategory(name, id);
        }
        emit finishedLoadCategorys();
    }





    reply->deleteLater();
}
