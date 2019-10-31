#ifndef CONNEXION_H
#define CONNEXION_H
#include <QString>
#include <QObject>

class IotConnexion : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ip READ getIP WRITE setIP NOTIFY IPChanged)
    Q_PROPERTY(float longitude READ getLongitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(float latitude READ getLatitude WRITE setLatitude NOTIFY latitudeChanged)

public:

    IotConnexion(QObject *parent=0);
    IotConnexion(const QString &ip, const float &latitude , const float &longitude, QObject *parent=0);
    IotConnexion(const IotConnexion & iotconn);
    IotConnexion & operator=(const IotConnexion & iotconn);

    QString getIP() const ;

    void setIP(const QString & ip);

    float getLongitude() const ;
    void  setLongitude(const float & longitude);
    float getLatitude() const ;
    void  setLatitude(const float & latitude);

signals:
    void latitudeChanged();
    void longitudeChanged();
    void IPChanged();

private:

    QString m_ip ;
    float m_longitude ;
    float m_latitude ;

};

#endif // CONNEXION_H
