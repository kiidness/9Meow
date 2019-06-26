#ifndef VOTE_H
#define VOTE_H

#include <QObject>

class Vote : public QObject
{
    Q_OBJECT
    QString m_imageId;
    int m_value;
public:
    explicit Vote(QString imageId, int value, QObject *parent = nullptr);

    QString imageId() const;
    int value() const;

signals:

public slots:
};

#endif // VOTE_H
