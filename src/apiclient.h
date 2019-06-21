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
    CategoryList *categoryList;

public:
    ApiClient(QObject *parent = nullptr);
    void getAllCategory(CategoryList *categoryList);

signals :
    void finishedLoad();
public slots:
    void onResult(QNetworkReply *reply);
};

#endif // APICLIENT_H
