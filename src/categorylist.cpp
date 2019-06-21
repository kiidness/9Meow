#include "categorylist.h"
#include "category.h"

CategoryList::CategoryList(QObject *parent) : QObject(parent), m_categories(QList<Category*>())
{

}


void CategoryList::connectCateg(int index)
{
    connect(m_categories[index], &Category::categoryChanged, this, [=](){emit categoryChanged(index);});
}
void CategoryList::disconnectCateg(int index)
{
    disconnect(m_categories[index], &Category::categoryChanged, this, 0);
}

void CategoryList::append(Category *category){
    emit preAppendCategory();
    int index = count();
    m_categories.append(category);
    connectCateg(index);

    emit postAppendCategory();
}

int CategoryList::count() const{
    return m_categories.count();
}

Category *CategoryList::at(int place) const{
    return m_categories.at(place);
}

void CategoryList::clear() {
    if (this->count() <= 0) {
        return;
    }
    for (int i = 0; i < this->count(); i++) {
        removeCategory(i);
    }
}

void CategoryList::remove(int index){
    emit preRemoveCategory(index);
    disconnectCateg(index);
    m_categories.removeAt(index);
    for(; index < count(); index++){
        disconnectCateg(index);
        connectCateg(index);
    }
    emit postRemoveCategory();
}

void CategoryList::createCategory(QString name, QString id)
{
    append(new Category(name, id));
}

void CategoryList::removeCategory(int position)
{
    emit preRemoveCategory(position);

    // No longer care for the file change
    disconnect ( m_categories[position], &Category::categoryChanged, this, 0);

    m_categories.removeAt(position);

    // Reconnect to good positions
    for ( ; position < count() ; ++position ) {
        disconnect ( m_categories[position], &Category::categoryChanged, this, 0);
        connect( m_categories[position], &Category::categoryChanged, this, [=](){ emit CategoryList::categoryChanged( position ); } );
    }
    emit postRemoveCategory();
}
