#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>

class Category : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged)

    QString m_name;
    QString m_id;

    public:
        explicit Category(QString name, QString id, QObject *parent = nullptr);
        QString name() const;
        QString id() const;
    signals:
        void nameChanged(QString name);
        void categoryChanged();

    public slots:
        void setid(QString id);
        void setname(QString name);
};

#endif // CATEGORY_H
