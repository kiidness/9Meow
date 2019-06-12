#include "apiclient.h"
#include "categorylist.h"

#include <QNetworkAccessManager>

ApiClient::ApiClient(QObject *parent): QObject(parent),
    networkManager(this)
{

    connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));
}

CategoryList *ApiClient::getAllCategory() {
    QUrl url("https://api.thecatapi.com/v1/breeds");
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply *currentReply = networkManager.get(request);
}

void ApiClient::onResult(QNetworkReply* reply){
    if(reply->error() != QNetworkReply::NoError)
        return;
    auto data = reply->readAll();
    int a = 1;
    /*QScriptEngine engine;
    QScriptValue result = engine.evaluate(data);*/
}
