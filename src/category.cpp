#include "category.h"

Category::Category(QString name, QObject *parent): QObject(parent), m_name(name) {
    connect(this, &Category::nameChanged, &Category::categoryChanged);
}
QString Category::name() const {
    return m_name;
}

void Category::setname(QString name) {
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}
