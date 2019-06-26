#ifndef CATIMAGEMODEL_H
#define CATIMAGEMODEL_H
#include <QAbstractListModel>
#include "catimagelist.h"


class CatImageModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(CatImageList *list READ list WRITE setList )
    CatImageList *m_catImageList;
public:
    explicit CatImageModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    CatImageList *list() const;

    void setList(CatImageList *list);


    QHash<int, QByteArray> roleNames() const;
    enum {
        CatImageName = Qt::UserRole,
        CatImageUrl,
        CatImageVote,
        CatImage
    };

protected:

public:
    Q_INVOKABLE void newElement();
    Q_INVOKABLE void removeRow(int index);
};


#endif // CATIMAGEMODEL_H
