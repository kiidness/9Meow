#include "catimagelist.h"
#include "catimage.h"

CatImageList::CatImageList(QObject *parent) : QObject(parent)
{

}


void CatImageList::connectCatImage(int index)
{
    connect(m_catImages[index], &CatImage::catImageChanged, this, [=](){emit catImageChanged(index);});
}
void CatImageList::disconnectCatImage(int index)
{
    disconnect(m_catImages[index], &CatImage::catImageChanged, this, 0);
}

void CatImageList::append(CatImage *catImage){
    emit preAppendCatImage();
    int index = count();
    m_catImages.append(catImage);
    connectCatImage(index);

    emit postAppendCatImage();
}

int CatImageList::count() const{
    return m_catImages.count();
}

CatImage *CatImageList::at(int place) const{
    return m_catImages.at(place);
}

void CatImageList::clear() {
    if (this->count() <= 0) {
        return;
    }
    for (int i = 0; i < this->count(); i++) {
        removeCatImage(i);
    }
}

void CatImageList::remove(int index){
    emit preRemoveCatImage(index);
    disconnectCatImage(index);
    m_catImages.removeAt(index);
    for(; index < count(); index++){
        disconnectCatImage(index);
        connectCatImage(index);
    }
    emit postRemoveCatImage();
}

void CatImageList::createCatImage(QString name, QString url)
{
    append(new CatImage(name, url));
}

void CatImageList::removeCatImage(int position)
{
    emit preRemoveCatImage(position);

    // No longer care for the file change
    disconnect ( m_catImages[position], &CatImage::catImageChanged, this, 0);

    m_catImages.removeAt(position);

    // Reconnect to good positions
    for ( ; position < count() ; ++position ) {
        disconnect ( m_catImages[position], &CatImage::catImageChanged, this, 0);
        connect( m_catImages[position], &CatImage::catImageChanged, this, [=](){ emit CatImageList::catImageChanged( position ); } );
    }
    emit postRemoveCatImage();
}
