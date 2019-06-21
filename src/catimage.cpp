#include "catimage.h"

CatImage::CatImage(QString name, QString url, QObject *parent)
    : QObject(parent), m_name(name), m_url(url)
{
    connect(this, &CatImage::nameChanged, &CatImage::catImageChanged);
    connect(this, &CatImage::urlChanged, &CatImage::catImageChanged);
}

QString CatImage::url() const
{
    return m_url;
}

QString CatImage::name() const
{
    return m_name;
}

void CatImage::setname(QString name) {
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void CatImage::seturl(QString url) {
    if (m_url == url)
        return;

    m_url = url;
    emit urlChanged(m_url);
}
