#ifndef CATIMAGE_H
#define CATIMAGE_H

#include <QObject>

class CatImage : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged)
    Q_PROPERTY(QString url READ name WRITE setname NOTIFY nameChanged)

    QString m_name;
    QString m_url;

public:
    explicit CatImage(QString name, QString url, QObject *parent = nullptr);
    QString name() const;
    QString url() const;

signals:
    void nameChanged(QString name);
    void urlChanged(QString url);
    void catImageChanged();

public slots:

    void setname(QString name);
    void seturl(QString url);
};

#endif // CATIMAGE_H
