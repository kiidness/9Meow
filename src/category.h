#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>

class Category : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged)

    QString m_name;

    public:
        explicit Category(QString name, QObject *parent = nullptr);
        QString name() const;
    signals:
        void nameChanged(QString name);
        void categoryChanged();

    public slots:

        void setname(QString name);
};

#endif // CATEGORY_H
