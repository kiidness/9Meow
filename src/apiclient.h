#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class CategoryList;

class ApiClient: public QObject
{
    Q_OBJECT
    QNetworkAccessManager networkManager;

public:
    ApiClient(QObject *parent = nullptr);
    CategoryList *getAllCategory();
public slots:
    void onResult(QNetworkReply *reply);
};

#endif // APICLIENT_H
