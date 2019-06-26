#include "vote.h"

QString Vote::imageId() const
{
    return m_imageId;
}

int Vote::value() const
{
    return m_value;
}

Vote::Vote(QString imageId, int value,QObject *parent) : QObject(parent), m_imageId(imageId), m_value(value)
{

}
