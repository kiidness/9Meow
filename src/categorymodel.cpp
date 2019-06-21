#include "categorymodel.h"
#include "categorylist.h"
#include "category.h"

#include <QDebug>
#include <QTextStream>

CategoryModel::CategoryModel(QObject *parent) : QAbstractListModel(parent), m_categoryList(nullptr)
{

}

CategoryList *CategoryModel::list() const
{
    return m_categoryList;
}

void CategoryModel::setList(CategoryList *categoryList)
{
    beginResetModel();

       if (m_categoryList)
           m_categoryList->disconnect(this);

       m_categoryList = categoryList;

       if (m_categoryList) {
           connect(m_categoryList, &CategoryList::preAppendCategory, this, [=]() {
               const int index = m_categoryList->count();        // Append implies end
               beginInsertRows(QModelIndex(), index, index);
           });
           connect(m_categoryList, &CategoryList::postAppendCategory, this, [=]() {
               endInsertRows();
           });

           connect(m_categoryList, &CategoryList::preRemoveCategory, this, [=](int index) {
               beginRemoveRows(QModelIndex(), index, index);
           });
           connect(m_categoryList, &CategoryList::postRemoveCategory, this, [=]() {
               endRemoveRows();
           });
           connect(m_categoryList, &CategoryList::categoryChanged,
                   this, [=](int row){ qDebug()<< "itemChanged " << row; emit CategoryModel::dataChanged(this->index(row), this->index(row)); });
       }

   endResetModel();
}

QHash<int, QByteArray> CategoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CategoryName] = "name";
    roles[Category]     = "category";

    return roles;
}

void CategoryModel::newElement()
{
    QString name(tr("Unknown"));
    QString id(tr("Unknown"));
    QTextStream stream(&name);
    stream << "-" << m_categoryList->count();

    m_categoryList->createCategory(name, id);
}

void CategoryModel::removeRow(int index)
{
    m_categoryList->removeCategory(index);
}

int CategoryModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if ( parent.isValid())
        return 0;

    return m_categoryList->count();
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto category = m_categoryList->at(index.row());

    switch (role) {
    case CategoryName:
        return category->name();
    case Category:
        return QVariant::fromValue(category);
    default:
        break;
    }
    return QVariant();
}

bool CategoryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {

        auto category = m_categoryList->at(index.row());

        switch (role) {
        case CategoryName:
            category->setname(value.toString());
            emit dataChanged(index, index, QVector<int>() << role);
        default:
            break;
        }
        return true;
    }
    return false;
}

Qt::ItemFlags CategoryModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}
