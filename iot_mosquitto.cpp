#include "iot_mosquitto.h"
#include "iot_connexion.h"

#include <QDebug>
#include <cstring>
#include <string>
#include <QVector>

StaticSignal * IotMosquitto::static_signal ;
IotMosquitto * IotMosquitto::m_instance = nullptr ;

IotMosquitto * IotMosquitto::create_instance(QString host, int port,int keepalive,bool clean_session){

    if (m_instance == nullptr)

        m_instance = new IotMosquitto(host,port,keepalive,clean_session);

    return m_instance ;

}

void IotMosquitto::delete_instance(){
     qDebug() << Q_FUNC_INFO << "\n" ;
     delete static_signal ;
     static_signal = nullptr ;
     delete m_instance ;
     m_instance = nullptr;

}

IotMosquitto::~IotMosquitto(){

    qDebug() << Q_FUNC_INFO << "\n" ;
    delete m_host ;
}

IotMosquitto::IotMosquitto(QString  host, int  port,int keepalive,bool  clean_session):m_port(port),m_keepalive(keepalive),m_clean_session(clean_session)

{

         IotMosquitto::static_signal = new StaticSignal();
         m_mosq = nullptr ;
         m_host = new char [host.toStdString().size() + 1] ;
         std::strncpy(m_host,host.toStdString().c_str(), host.toStdString().size() +1);

         connect(static_signal, &StaticSignal::mosquittoReady, this, &IotMosquitto::handle_subscribe);
         connect(static_signal, &StaticSignal::mosqMsgReceived, this, &IotMosquitto::handle_msg);
         connect(static_signal, &StaticSignal::mosquittoNotReady, this, &IotMosquitto::handle_not_ready);
         connect(static_signal, &StaticSignal::mosquittoDisconnected, this, &IotMosquitto::handle_disconnection);

}


void IotMosquitto::handle_disconnection(){

    qDebug() << Q_FUNC_INFO << "\n" ;

    mosquitto_destroy(m_mosq);
    mosquitto_lib_cleanup();
    _started = false ;
    emit mosquittoStoped();
}

void IotMosquitto::handle_error(){

    // add a generic signal with QString message
    qDebug() << Q_FUNC_INFO << "\n" ;
}

void IotMosquitto::handle_not_ready(){

    qDebug() << Q_FUNC_INFO << "\n" ;
    emit mosquittoNotConnected("Mosquitto connection not ready");
}


void IotMosquitto::handle_msg(QString topic , QString msg){


    qDebug() << "handle_msg, " << "topic : " << topic << "message : " << msg << "\n";
    emit mosqMsgReceived(topic,msg);
}

void IotMosquitto::handle_subscribe(){

    emit mosquittoConnected();
}

void IotMosquitto::subsribe(QString topic){

    char * topic_name = new char [topic.toStdString().size() + 1] ;
    std::strncpy(topic_name,topic.toStdString().c_str(), topic.toStdString().size() +1);
    mosquitto_subscribe(m_mosq, nullptr, topic_name, 2) ;
}

void IotMosquitto::unsubsribe(QString topic){

    char * topic_name = new char [topic.toStdString().size() + 1] ;
    std::strncpy(topic_name,topic.toStdString().c_str(), topic.toStdString().size() +1);
    mosquitto_unsubscribe(m_mosq, nullptr, topic_name) ;
}

void IotMosquitto::start_mosquitto(){


    qDebug() << Q_FUNC_INFO << "\n" ;
    mosquitto_lib_init();

    m_mosq = mosquitto_new(nullptr, m_clean_session, nullptr);

    if(!m_mosq){

        qDebug() << "Error: Out of memory.\n";
        return ;
     }

     mosquitto_log_callback_set(m_mosq, my_log_callback);
     mosquitto_connect_callback_set(m_mosq, my_connect_callback);
     mosquitto_message_callback_set(m_mosq, my_message_callback);
     mosquitto_subscribe_callback_set(m_mosq, my_subscribe_callback);
     mosquitto_disconnect_callback_set(m_mosq,my_disconnect_callback);

     if(mosquitto_connect(m_mosq, m_host, m_port, m_keepalive)){

         qDebug() << "Coult not connect to mosquitto server.\n";
         mosquitto_destroy(m_mosq);
         mosquitto_lib_cleanup();
         emit mosquittoNotConnected("Coult not connect to mosquitto server.");
         return ;
     }

     if(mosquitto_loop_start(m_mosq)){

         qDebug() << "Unable to start mosquitto server.\n" ;
         mosquitto_destroy(m_mosq);
         mosquitto_lib_cleanup();
         emit mosquittoNotConnected("Unable to start mosquitto server.\n" );
         return ;

     }

     _started = true ;

 }


void IotMosquitto::stop_mosquitto() {

    if (! _started){
        qDebug() << "Mosquitto not started\n" ;
        return ;
    }
    qDebug() << Q_FUNC_INFO << "\n" ;
    if(!m_mosq)
        return ;
    if(mosquitto_disconnect(m_mosq))
        qDebug() << "Error when disconnecting from mosquitto server"  << Q_FUNC_INFO << "\n" ;

}


void IotMosquitto::my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{

    Q_UNUSED(mosq);
    Q_UNUSED(userdata);

    if(message->payloadlen){

        QString  * topic = new QString(message->topic);

        QString * msg = new QString((char*)message->payload) ;

        static_signal->sendMosqMsgReceived(*topic,*msg);

        delete topic ;
        delete msg ;
    }
    else{
        qDebug() << message->topic << "\n";
    }

        fflush(stdout);

}

void IotMosquitto::my_disconnect_callback(struct mosquitto *mosq, void *userdata, int result)

{
    Q_UNUSED(userdata);
   // Q_UNUSED(mosq);

    if(!result){

        qDebug() << "my_disconnect call back, " << Q_FUNC_INFO << "\n " ;

        if(mosquitto_loop_stop(mosq,false) ){
            qDebug() << "Mosquitto server failed to stop" << Q_FUNC_INFO << "\n" ;
            return ;
        }

        emit static_signal->sendMosquittoDisconnected();

    }else{
        qDebug() <<  "Disconnect failed" << Q_FUNC_INFO << "\n";
    }

}


void IotMosquitto::my_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
    Q_UNUSED(mosq);
    Q_UNUSED(userdata);
    if(!result){

        /* Subscribe to broker information topics on successful connect. */
        static_signal->sendMosquittoReady();
        qDebug() << "my_connect call back \n " ;

    }else{
        qDebug() << "Connect failed \n";
        static_signal->sendMosquittoNotReady();
    }
}

void IotMosquitto::my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
    Q_UNUSED(mosq);
    Q_UNUSED(userdata);

    qDebug() << "Subscribed (mid:" << mid <<"): " << granted_qos[0] << "\n";

    for(int i=1; i<qos_count; i++){

        qDebug() << ", " << granted_qos[i] << "\n";
    }

    qDebug() << "\n";
}

void IotMosquitto::my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
    Q_UNUSED(level);
    Q_UNUSED(mosq);
    Q_UNUSED(userdata);
    /* Pring all log messages regardless of level. */
    qDebug() << str << "\n";
}

