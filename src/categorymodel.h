#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H
#include <QAbstractListModel>

class CategoryList;

class CategoryModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(CategoryList *list READ list WRITE setList )
    CategoryList *m_categoryList;
public:
    explicit CategoryModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    CategoryList *list() const;

    void setList(CategoryList *list);


    QHash<int, QByteArray> roleNames() const;
    enum {
        CategoryName = Qt::UserRole,
        Size,
        Category
    };

protected:

public:
    Q_INVOKABLE void newElement();
    Q_INVOKABLE void removeRow(int index);
};

#endif // CATEGORYMODEL_H
