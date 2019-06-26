#ifndef CATIMAGE_H
#define CATIMAGE_H

#include <QObject>

class CatImage : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged)
    Q_PROPERTY(QString url READ name WRITE setname NOTIFY nameChanged)
    Q_PROPERTY(int vote READ vote WRITE setvote NOTIFY voteChanged)

    QString m_name;
    QString m_url;
    int m_vote;

public:
    explicit CatImage(QString name, QString url, QObject *parent = nullptr);
    QString name() const;
    QString url() const;
    int vote() const;


signals:
    void nameChanged(QString name);
    void urlChanged(QString url);
    void voteChanged(int vote);
    void catImageChanged();

public slots:

    void setname(QString name);
    void seturl(QString url);
    void setvote(int vote);
};

#endif // CATIMAGE_H
