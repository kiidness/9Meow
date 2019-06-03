#include "categorylist.h"

CategoryList::CategoryList(QObject *parent) : QObject(parent), m_categories(QList())
{

}


void CategoryList::connectCateg(int index)
{
    connect(m_categories[index], &Category::categoryChanged, this, [=](){emit itemChanged(index);});
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

int CategoryList::count(){
    return m_categories.count();
}

Category CategoryList::at(int place) const{
    return m_categories.at(place);
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
