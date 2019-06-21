#include "category.h"

Category::Category(QString name, QString id, QObject *parent): QObject(parent), m_name(name), m_id(id) {
    connect(this, &Category::nameChanged, &Category::categoryChanged);
}
QString Category::name() const {
    return m_name;
}

QString Category::id() const
{
    return m_id;
}

void Category::setname(QString name) {
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Category::setid(QString id) {
    if (m_id == id)
        return;

    m_id = id;
}
