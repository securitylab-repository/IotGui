#include "iot_connexion.h"

IotConnexion::IotConnexion(QObject *parent):QObject(parent)
{}

IotConnexion::IotConnexion(const QString &ip, const float &latitude , const float &longitude, QObject *parent)
    : QObject(parent) , m_ip(ip) , m_latitude(latitude), m_longitude(longitude)
{
}

IotConnexion::IotConnexion(const IotConnexion & iotconn){

    m_ip = iotconn.m_ip ;
    m_longitude = iotconn.m_longitude ;
    m_latitude = iotconn.m_latitude ;
}

IotConnexion & IotConnexion::operator=(const IotConnexion & iotconn){

    if(this != &iotconn){

        this->m_ip = iotconn.m_ip ;
        this->m_longitude = iotconn.m_longitude ;
        this->m_latitude = iotconn.m_latitude ;
    }
    return *this ;
}

QString IotConnexion::IotConnexion::getIP() const {

    return m_ip ;
}

void IotConnexion::setIP(const QString & ip){

    if (m_ip != ip){

        m_ip = ip ;
        emit IPChanged();
    }
}

float IotConnexion::getLongitude() const {

    return m_longitude ;
}

void  IotConnexion::setLongitude(const float & longitude) {

    if(m_longitude != longitude){

        m_longitude = longitude ;
        emit longitudeChanged();
    }
}

float IotConnexion::getLatitude() const {

    return m_latitude;
}

void  IotConnexion::setLatitude(const float & latitude){

    if (m_latitude != latitude){

        m_latitude = latitude ;
        emit latitudeChanged();
    }
}
