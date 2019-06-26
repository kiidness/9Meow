#include "catimagemodel.h"
#include "catimage.h"

#include <QDebug>
#include <QTextStream>


CatImageModel::CatImageModel(QObject *parent)
    : QAbstractListModel(parent), m_catImageList(nullptr)
{

}

CatImageList *CatImageModel::list() const
{
    return m_catImageList;
}

void CatImageModel::setList(CatImageList *catImageList)
{
    beginResetModel();

       if (m_catImageList)
           m_catImageList->disconnect(this);

       m_catImageList = catImageList;

       if (m_catImageList) {
           connect(m_catImageList, &CatImageList::preAppendCatImage, this, [=]() {
               const int index = m_catImageList->count();        // Append implies end
               beginInsertRows(QModelIndex(), index, index);
           });
           connect(m_catImageList, &CatImageList::postAppendCatImage, this, [=]() {
               endInsertRows();
           });

           connect(m_catImageList, &CatImageList::preRemoveCatImage, this, [=](int index) {
               beginRemoveRows(QModelIndex(), index, index);
           });
           connect(m_catImageList, &CatImageList::postRemoveCatImage, this, [=]() {
               endRemoveRows();
           });
           connect(m_catImageList, &CatImageList::catImageChanged,
                   this, [=](int row){ qDebug()<< "itemChanged " << row; emit CatImageModel::dataChanged(this->index(row), this->index(row)); });
       }

   endResetModel();
}

QHash<int, QByteArray> CatImageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CatImageName] = "name";
    roles[CatImageUrl] = "url";
    roles[CatImageVote] = "vote";
    roles[CatImage]     = "catImage";

    return roles;
}

void CatImageModel::newElement()
{
    QString name(tr("Unknown"));
    QString url(tr("Unknown"));
    QTextStream stream(&name);
    stream << "-" << m_catImageList->count();

    m_catImageList->createCatImage(name, url);
}

void CatImageModel::removeRow(int index)
{
    m_catImageList->removeCatImage(index);
}

int CatImageModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if ( parent.isValid())
        return 0;

    return m_catImageList->count();
}

QVariant CatImageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto catImage = m_catImageList->at(index.row());

    switch (role) {
    case CatImageName:
        return catImage->name();
    case CatImageUrl :
        return catImage->url();
    case CatImageVote :
        return catImage->vote();
    case CatImage:
        return QVariant::fromValue(catImage);
    default:
        break;
    }
    return QVariant();
}

bool CatImageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {

        auto catImage = m_catImageList->at(index.row());

        switch (role) {
        case CatImageName:
            catImage->setname(value.toString());
            emit dataChanged(index, index, QVector<int>() << role);
        case CatImageUrl:
            catImage->seturl(value.toString());
            emit dataChanged(index, index, QVector<int>() << role);
        case CatImageVote:
            catImage->setvote(value.toInt());
            emit dataChanged(index, index, QVector<int>() << role);
        default:
            break;
        }
        return true;
    }
    return false;
}

Qt::ItemFlags CatImageModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}
