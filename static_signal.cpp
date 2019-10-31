#include "static_signal.h"

StaticSignal::StaticSignal(QObject *parent) : QObject(parent)
{

}

void StaticSignal::sendMosquittoNotReady(){


    emit sendMosquittoNotReady();

}

void StaticSignal::sendMosquittoReady(){


    emit mosquittoReady();

}
void StaticSignal::sendGpsReceived(float lat,float lon) {

    emit gpsReceived(lat,lon);
}


void StaticSignal::sendMosqMsgReceived(QString topic,QString msg){

    emit mosqMsgReceived(topic,msg);
}

void StaticSignal::sendMosquittoDisconnected(){

    emit mosquittoDisconnected();
}
