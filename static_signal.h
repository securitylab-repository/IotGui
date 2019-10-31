#ifndef STATIC_SIGNAL_H
#define STATIC_SIGNAL_H

#include <QObject>

class StaticSignal : public QObject
{
    Q_OBJECT
public:
    explicit StaticSignal(QObject *parent = nullptr);

    void sendMosquittoReady();
    void sendGpsReceived(float,float);
    void sendMosqMsgReceived(QString,QString);
    void sendMosquittoNotReady();
    void sendMosquittoDisconnected();

signals:

    void mosquittoReady();
    void gpsReceived(float,float);
    void mosqMsgReceived(QString,QString);
    void mosquittoNotReady();
    void mosquittoDisconnected();

public slots:
};

#endif // STATIC_SIGNAL_H
