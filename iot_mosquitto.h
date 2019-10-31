#ifndef IOT_MOSQUITTO_H
#define IOT_MOSQUITTO_H

#include <QString>
#include <mosquitto.h>
#include <QObject>
#include <QtCore>
#include <QMutex>

#include "iot_mesures_model.h"
#include "static_signal.h"
#include "iot_model.h"

class IotMosquitto : public QObject {

    Q_OBJECT

public:



    static void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    static void my_connect_callback(struct mosquitto *mosq, void *userdata, int result);
    static void my_disconnect_callback(struct mosquitto *mosq, void *userdata, int result);

    static void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos);
    static void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str);
    void start_mosquitto();
    void subsribe(QString);
    void unsubsribe(QString);
    void stop_mosquitto();

    static StaticSignal * static_signal ;
    static IotMosquitto * create_instance(QString host, int port,int keepalive,bool clean_session);
    static void delete_instance();
public slots:

    void handle_subscribe();
    void handle_msg(QString,QString);
    void handle_error();
    void handle_disconnection();
    void handle_not_ready();

signals :

    void mosquittoConnected() ;
    void mosquittoStoped() ;
    void mosqMsgReceived(QString,QString);
    void mosquittoNotConnected(QString);

private:

    static IotMosquitto *  m_instance ;
    char *m_host ;
    static bool stat ;
    int  m_port ;
    int  m_keepalive;
    bool m_clean_session ;
    struct mosquitto *m_mosq ;
    bool _started {false} ;

    IotMosquitto(QString host, int port,int keepalive,bool clean_session);
     ~IotMosquitto();
};
#endif // IOT_MOSQUITTO_H
