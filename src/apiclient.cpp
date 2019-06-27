#include "apiclient.h"
#include "categorylist.h"
#include "category.h"
#include "catimagelist.h"
#include "vote.h"
#include "catimage.h"

#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QUrlQuery>
#include <QtNetwork>

ApiClient::ApiClient(QObject *parent): QObject(parent),
    networkManager(this)
{

    //connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));
}

void ApiClient::getAllCategory(CategoryList *list) {
    QUrl url("https://api.thecatapi.com/v1/breeds");
    QNetworkRequest request;
    request.setUrl(url);

    categoryList = list;
    QNetworkReply *reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::onCategoryResult);
    connectErrorReplySlot(reply);
}

void ApiClient::getAllImages(QString categoryName, CatImageList *list)
{
    QUrl url("https://api.thecatapi.com/v1/images/search?limit=20&breed_ids="+categoryName);
    QNetworkRequest request;
    request.setUrl(url);

    catImageList = list;
    QNetworkReply *reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::onCatImageResult);
    connectErrorReplySlot(reply);
}

void ApiClient::connectErrorReplySlot(QNetworkReply *reply)
{
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void ApiClient::updateAllVotes()
{
    QUrl url("https://api.thecatapi.com/v1/votes");
    QNetworkRequest request;
    request.setRawHeader("x-api-key","17d94b92-754f-46eb-99a0-65be65b5d18f");
    request.setUrl(url);
    QNetworkReply *reply  = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::onVoteResult);
    connectErrorReplySlot(reply);
}

void ApiClient::getAllVotes(QList<Vote*> *list)
{
    voteList = list;
    updateAllVotes();
}

QJsonArray ApiClient::replyToJson(QNetworkReply *reply)
{
    QByteArray result = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result);

    QJsonArray array = jsonResponse.array();


    return array;
}

void ApiClient::onVoteResult(){
    QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
    if(reply->error() != QNetworkReply::NoError)
        return;
    QJsonArray array = replyToJson(reply);
    voteList->clear();
    for(const QJsonValue& value : array){
        QJsonObject obj = value.toObject();
        QString id = obj["image_id"].toString();
        int vote = obj["value"].toInt();
        voteList->append(new Vote(id,vote));
    }
    reply->deleteLater();
}

void ApiClient::onCategoryResult(){
    QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
    if(reply->error() != QNetworkReply::NoError)
        return;
    QJsonArray array = replyToJson(reply);
    categoryList->clear();
    for(const QJsonValue& value : array) {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        QString id = obj["id"].toString();
        categoryList->createCategory(name, id);
    }
    emit finishedLoadCategorys();
    reply->deleteLater();
}

void ApiClient::onCatImageResult(){
    QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
    if(reply->error() != QNetworkReply::NoError)
        return;
    QJsonArray array = replyToJson(reply);
    catImageList->clear();
    for(const QJsonValue& value : array) {
        QJsonObject obj = value.toObject();
        QString name = obj["id"].toString();
        int voteValue = 0;
        if(voteList){
            QList<Vote*>::iterator itr = std::find_if(voteList->begin(), voteList->end(), [=](Vote* vote) { return vote->imageId() == name; });
                if(itr != voteList->end()) {
                    foreach (Vote *vote, (*voteList)) {
                        if(vote->imageId()==name){
                            if(vote->value() == 1){
                                voteValue +=1;
                            }else{
                                voteValue -=1;
                            }
                        }
                    }
                }

        }
        QString url = obj["url"].toString();
        catImageList->createCatImage(name, url, voteValue);
    }
    emit finishedLoadCatImages();
    reply->deleteLater();
}

void ApiClient::slotError(QNetworkReply::NetworkError error){
    qDebug() << "error api code return no succes" << error;
}

void ApiClient::postVote(QString image, int value){
    foreach (CatImage *catImage, catImageList->catImages()) {
        if(catImage->name() == image){
            if(value == 1){
                catImage->setvote(catImage->vote()+1);
            }else{
                catImage->setvote(catImage->vote()-1);
            }
            catImage->setIsvoted(true);
        }
    }
    QJsonObject json;
    json.insert("image_id", image);
    json.insert("value", QString(value));
    QNetworkRequest request;
    QUrl url("https://api.thecatapi.com/v1/votes");
    request.setRawHeader("x-api-key","17d94b92-754f-46eb-99a0-65be65b5d18f");
    request.setUrl(url);
    request.setRawHeader("Content-Type", "application/json");
    QNetworkReply *reply  = networkManager.post(request, QJsonDocument(json).toJson());
    connectErrorReplySlot(reply);
}

