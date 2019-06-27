#include "catimage.h"

int CatImage::vote() const
{
    return m_vote;
}

void CatImage::setvote(int vote)
{
    m_vote = vote;
    emit voteChanged(vote);
}

int CatImage::isvoted() const
{
    return m_isvoted;
}

void CatImage::setisvoted(int isVoted)
{
    m_isvoted = isVoted;
    emit isvotedChanged(isVoted);
}

CatImage::CatImage(QString name, QString url, int vote = 0, QObject *parent)
    : QObject(parent), m_name(name), m_url(url), m_vote(vote)
{
    m_isvoted = 0;
    connect(this, &CatImage::nameChanged, &CatImage::catImageChanged);
    connect(this, &CatImage::urlChanged, &CatImage::catImageChanged);
    connect(this, &CatImage::voteChanged, &CatImage::catImageChanged);
    connect(this, &CatImage::isvotedChanged, &CatImage::catImageChanged);
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
