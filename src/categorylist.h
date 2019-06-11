#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H

#include <QObject>
#include <QList>

class Category;

class CategoryList : public QObject
{
    Q_OBJECT
    QList<Category*> m_categories;
public:
    explicit CategoryList(QObject *parent = nullptr);

    void append(Category *category);
    Category *at(int place) const;
    int count() const;
    void remove(int index);

    void connectCateg(int index);

    void disconnectCateg(int index);
    void createCategory(QString name);
    void removeCategory(int position);

signals:
    void preAppendCategory();
    void postAppendCategory();
    void preRemoveCategory(int index);
    void postRemoveCategory();

    void categoryChanged(int index);
public slots:
};

#endif // CATEGORYLIST_H
