#ifndef CATIMAGELIST_H
#define CATIMAGELIST_H

#include <QObject>
#include <QList>

class CatImage;

class CatImageList : public QObject
{
    Q_OBJECT
    QList<CatImage*> m_catImages;
public:
    explicit CatImageList(QObject *parent = nullptr);
    void append(CatImage *catImage);
    CatImage *at(int place) const;
    int count() const;
    void remove(int index);

    void connectCatImage(int index);

    void disconnectCatImage(int index);
    void createCatImage(QString name, QString url);
    void removeCatImage(int position);
    void clear();

signals:
    void preAppendCatImage();
    void postAppendCatImage();
    void preRemoveCatImage(int index);
    void postRemoveCatImage();

    void catImageChanged(int index);
public slots:
};

#endif // CATIMAGELIST_H
