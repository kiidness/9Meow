#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class CategoryList;
class Category;
class CatImageList;

class ApiClient: public QObject
{
    Q_OBJECT
    QNetworkAccessManager networkManager;
    CategoryList *categoryList;
    CatImageList *catImageList;

public:
    ApiClient(QObject *parent = nullptr);
    void getAllCategory(CategoryList *categoryList);
    Q_INVOKABLE void getAllImages(QString categoryName, CatImageList *list);

signals :
    void finishedLoadCategorys();
    void finishedLoadCatImages();
public slots:
    void onResult(QNetworkReply *reply);
};

#endif // APICLIENT_H
