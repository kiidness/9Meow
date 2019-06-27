#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class CategoryList;
class Category;
class CatImageList;
class Vote;

class ApiClient: public QObject
{
    Q_OBJECT
    QNetworkAccessManager networkManager;
    CategoryList *categoryList;
    CatImageList *catImageList;
    QList<Vote*> *voteList;

public:
    ApiClient(QObject *parent = nullptr);
    void getAllCategory(CategoryList *categoryList);
    Q_INVOKABLE void getAllImages(QString categoryName, CatImageList *list);
    Q_INVOKABLE void getAllVotes(QList<Vote *> *list);

    QJsonArray replyToJson(QNetworkReply *reply);

    void connectErrorReplySlot(QNetworkReply *reply);


    Q_INVOKABLE void postVote(QString image, int value);
    Q_INVOKABLE void updateAllVotes();

signals :
    void finishedLoadCategorys();
    void finishedLoadCatImages();
public slots:
    void onVoteResult();
    void slotError(QNetworkReply::NetworkError error);
    void onCategoryResult();
    void onCatImageResult();
};

#endif // APICLIENT_H
