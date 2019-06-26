#include "apiclient.h"
#include "categorylist.h"
#include "category.h"
#include "catimagelist.h"
#include "vote.h"

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

void ApiClient::getAllVotes(QList<Vote*> *list)
{
    voteList = list;
    QUrl url("https://api.thecatapi.com/v1/votes");
    QNetworkRequest request;
    request.setRawHeader("x-api-key","17d94b92-754f-46eb-99a0-65be65b5d18f");
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
    if(a["value"].toInt() == 1){
        qDebug() << "avalueIf" << a["value"];
        voteList->clear();
        for(const QJsonValue& value : array){
            QJsonObject obj = value.toObject();
            QString id = obj["image_id"].toString();
            int vote = obj["value"].toInt();
            voteList->append(new Vote(id,vote));
        }
    }else{

    if(a["url"].toString() != ""){
        catImageList->clear();
        for(const QJsonValue& value : array) {
            QJsonObject obj = value.toObject();
            QString name = obj["id"].toString();
            if(voteList){
                QList<Vote*>::iterator itr = std::find_if(voteList->begin(), voteList->end(), [=](Vote* vote) { return vote->imageId() == name; });
                    if(itr != voteList->end()) {
                        qDebug() << "it" << (*itr);
                    }
            }
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
    }





    reply->deleteLater();
}
