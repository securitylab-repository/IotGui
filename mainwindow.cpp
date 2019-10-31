#include <QQuickWidget>
#include <QMdiSubWindow>
#include <QQmlContext>
#include <QThread>

#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

#include <regex>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iot_connexion.h"
#include "iot_mosquitto.h"
#include "iot_mesures_model.h"
#include "iot_treeview.h"
#include "iot_mdiwindow_mesures_array.h"
#include "iot_chart_view.h"
#include "iot_mosq_conn_dialog.h"
#include "iot_sub_dialog.h"
#include "iot_delete_sub_dialog.h"
#include <QVector>

#include <QtConcurrent/QtConcurrentRun>

#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_Connection_Mosquitto,&QAction::triggered,this, &MainWindow::printMosquittoConnDialog);
    connect(ui->action_Subscribe,&QAction::triggered,this, &MainWindow::printMosquittoSubDialog);
    connect(ui->action_Remove_Subscribe,&QAction::triggered,this, &MainWindow::printMosquittoDelSubDialog);
    connect(ui->action_Stop_Mosquitto,&QAction::triggered,this, &MainWindow::stopMosquitto);
    connect(ui->action_quitter,&QAction::triggered,this, &MainWindow::quitter);

    mesures_submenu  = new QMenu("Mesures View");
    ui->menu_affichage->addMenu(mesures_submenu);

    /* map view initisalisation and showing */
    mapInit();
}

MainWindow::~MainWindow()

{

 //   mosq->stop_mosquitto();

}

/*!
 * \brief MainWindow::printMosquittoSubDialog
 * \return void
 *
 * This function executes and show IotSubDialog, that gets subscribtion informations from user
 */

void MainWindow::printMosquittoSubDialog(){

   IotSubDialog * dialo = new IotSubDialog(this);
   connect(dialo,&IotSubDialog::topicMesureNames, this,&MainWindow::handleSubscribe);
   dialo->exec();
}


/*!
 * \brief MainWindow::handleSubscribe
 * \param topic
 * \param mesures
 * \return void
 *
 * This slot is called from IotSubDialog through a topicMesuresNames signal
 */
void MainWindow::handleSubscribe(QString topic,QVector<QString> mesures){


    // check if a topic already exists
    if(topic_model_dic.contains(topic))
        return ;

    // store topic in list
     subscribed_topics_list << topic ;

   //  subscribe to gps infos from topic
    mosq->subsribe(topic+"/gps");

    IotMesuresModel * model = new IotMesuresModel() ;

    mosq->subsribe(topic);

    model->addColumn("Time") ;
    for (auto & mesure : mesures){

        model->addColumn(mesure);
    }

    topic_model_dic.insert(topic,model);

    mesure_names = mesures ;

    /* add submenu for a topic to Affichage --> mesures view */
    QAction * action = new QAction(topic);
    mesures_submenu->addAction(action);
    this->topic_action_dic[topic] = action ;

    IotMdiWindowMesuresArray * mdi_mesures_array = new IotMdiWindowMesuresArray(this,topic) ;
    IotTreeView *  mesures_view = new IotTreeView(model,nullptr,topic);
    mdi_mesures_array->addWidget(mesures_view);

    // fore delete, we can store mdi_mesures_array in QHash with topic as key ?
    // In this case we must disconnect this connection
    topic_mdiwindow_dic[topic] = mdi_mesures_array ;
    connect(action,&QAction::triggered,mdi_mesures_array,&IotMdiWindowMesuresArray::prepareWindow);
    connect(mdi_mesures_array,&IotMdiWindow::newMdiWindowAdded,this,&MainWindow::printTabMesures);

    connect(mesures_view,&IotTreeView::menuActionClicked,this,&MainWindow::printGraph);
}

void MainWindow::printMosquittoDelSubDialog(){

   IotDelSubDialog *  dialo = new IotDelSubDialog(this,subscribed_topics_list);
   connect(dialo,&IotDelSubDialog::topicDeleted, this,&MainWindow::deleteSubscribe);
   dialo->exec();
}

void MainWindow::deleteSubscribe(QVector<QString> topics){

    qDebug() << Q_FUNC_INFO << "\n";

    /*remove subscribed topics from mosquitto and gui*/
    for(auto & topic : topics){

        qDebug() << topic << "\n";
        delete topic_model_dic[topic] ;
        topic_model_dic.remove(topic);

        topic_mdiwindow_dic[topic]->close() ;
        delete topic_mdiwindow_dic[topic];
        topic_mdiwindow_dic.remove(topic);

        mesures_submenu->removeAction(topic_action_dic[topic]);
        delete topic_action_dic[topic];
        topic_action_dic.remove(topic);

        std::string reg = topic.toStdString() + ".*";
        std::regex topicregex(reg) ;
        for (QString & topicmesur : topic_metric_graph_dic.keys()){

            if(std::regex_match(topicmesur.toStdString(),topicregex)){

                topic_metric_graph_dic[topicmesur]->close();
                delete topic_metric_graph_dic[topicmesur] ;
                topic_metric_graph_dic.remove(topicmesur);
            }
        }

        /* unsubscribe from mosquitto server */
        mosq->unsubsribe(topic) ;
        mosq->unsubsribe(topic+"/gps") ;

        /*remove topic from subscribed topic list*/
        subscribed_topics_list.removeOne(topic);
    }
}


void MainWindow::printTabMesures(QWidget * mdiwin ){

    IotMdiWindowMesuresArray * win = (IotMdiWindowMesuresArray*)mdiwin ;
    ui->mdi->addSubWindow(win);
    win->show();
    ui->mdi->tileSubWindows();
}


void MainWindow::printGraph(QString topic , QString action) {


    if(topic_metric_graph_dic.contains(topic+action)) {

        if(!topic_metric_graph_dic[topic+action]->isVisible())
            topic_metric_graph_dic[topic+action]->show();

        return ;

    }
    IotChartView * chart_view = new IotChartView(topic_model_dic[topic],topic_model_dic[topic]->getIndexOfColumn(action),nullptr);
    //chart_view->setAttribute(Qt::WA_DeleteOnClose);
    IotMdiWindowGraph * mdi_graph = new IotMdiWindowGraph(this,"Graph " + topic + " " + action );
    //mdi_graph->setAttribute(Qt::WA_DeleteOnClose);
    mdi_graph->addWidget(chart_view);
    ui->mdi->addSubWindow(mdi_graph);
    mdi_graph->show();
    ui->mdi->tileSubWindows();
    topic_metric_graph_dic[topic+action] = mdi_graph ;

}

void MainWindow::printMosquittoConnDialog(){

   IotMosqConnDialog * dialo = new IotMosqConnDialog(this);
   connect(dialo,&IotMosqConnDialog::ipPort,this,&MainWindow::mosquitoConnect);
   dialo->exec();

}


void MainWindow::mosquitoConnect(QString ip, int port){

    mosq =IotMosquitto::create_instance(ip, port,60,true);

    /*mosq->moveToThread(&mqttThread);
    connect(&mqttThread, &QThread::finished, mosq, &QObject::deleteLater);
    connect(this, &MainWindow::start_mosquitto_sig, mosq, &IotMosquitto::start_mosquitto);
    mqttThread.start();
    emit start_mosquitto_sig();*/

    //QFuture<void> f1 =QtConcurrent::run(mosq,&IotMosquitto::start_mosquitto);

    connect(mosq,&IotMosquitto::mosquittoConnected,this,&MainWindow::handleMosqConnected);
    connect(mosq,&IotMosquitto::mosqMsgReceived,this,&MainWindow::handleMosqMsg);
    connect(mosq,&IotMosquitto::mosquittoNotConnected,this,&MainWindow::mosquitoNotConnected);
    connect(mosq,&IotMosquitto::mosquittoStoped,this,&MainWindow::handleMosqStoped);

    mosq->start_mosquitto();

    ip_mosquitto = ip ;
}

void MainWindow::handleMosqConnected(){

    ui->action_Connection_Mosquitto->setEnabled(false);
    ui->action_Subscribe->setEnabled(true);
    ui->action_Stop_Mosquitto->setEnabled(true);
    ui->statusBar->showMessage("Connected to mosquitto server");

   }


void MainWindow::mosquitoNotConnected(QString msg){

    qDebug() << Q_FUNC_INFO << "\n" ;
    IotMosquitto::delete_instance();
    mosq = nullptr ;
    ui->statusBar->showMessage(msg);


}


void MainWindow::stopMosquitto(){

    qDebug() << Q_FUNC_INFO << "\n";
    if(! mosq){

        qDebug() << "Mosquitto object not created yet\n" ;

        return ;
    }

    mosq->stop_mosquitto();

}

void MainWindow::handleMosqStoped(){

    qDebug() << Q_FUNC_INFO << "\n";
    for ( auto & topic : topic_model_dic.keys()){

        delete topic_model_dic[topic] ;
        topic_model_dic.remove(topic);
        /* unsubscribe from mosquitto server */
        mosq->unsubsribe(topic) ;
        mosq->unsubsribe(topic+"/gps") ;
    }

    for (auto & topic : topic_mdiwindow_dic.keys()){

        topic_mdiwindow_dic[topic]->close() ;

        delete topic_mdiwindow_dic[topic];
        topic_mdiwindow_dic.remove(topic);
    }

    for (auto & topic : topic_action_dic.keys()){

          mesures_submenu->removeAction(topic_action_dic[topic]);
          delete topic_action_dic[topic];
          topic_action_dic.remove(topic);
    }

    for (auto & topicmesur : topic_metric_graph_dic.keys()){

        topic_metric_graph_dic[topicmesur]->close();
        delete topic_metric_graph_dic[topicmesur] ;
        topic_metric_graph_dic.remove(topicmesur);
    }

    /*remove all topics from subscribed topic list*/
    subscribed_topics_list.clear();

    ui->action_Connection_Mosquitto->setEnabled(true);
    ui->action_Stop_Mosquitto->setEnabled(false);
    ui->action_Subscribe->setEnabled(false);
    IotMosquitto::delete_instance();
    /*mqttThread.quit();
    mqttThread.wait();*/
    mosq = nullptr ;
    ui->statusBar->showMessage("Mosquitto connection stopped");


}


void MainWindow::handleMosqMsg(QString topic, QString msg){

   qDebug() << "MainWindow::handleMosqMsg"  << topic << msg << "\n" ;
   auto jsondata =QJsonDocument::fromJson(msg.toUtf8());
   if(jsondata.isNull()){

       qDebug()<<"Failed to create JSON doc.";
       exit(2);
   }

   if(!jsondata.isObject()){

       qDebug()<<"JSON is not an object.";
       exit(3);
   }

   QJsonObject json_obj =jsondata.object();

   if(json_obj.isEmpty()){

       qDebug()<<"JSON object is empty.";
       exit(4);
   }

   // for gps info the topic must be in form /iot/[0-9]+/gps
   std::string reg = "iot/[0-9]+/gps";
   std::regex topicregex(reg) ;
   if(std::regex_match(topic.toStdString(),topicregex)){

       QVariantMap json_map = json_obj.toVariantMap();
       qDebug() << "Latitude : " << json_map["la"].toFloat() << "Longitude : " << json_map["lo"].toFloat() << "\n" ;
       handleGps(json_map["la"].toFloat(),json_map["lo"].toFloat());

   }

   else{
       QVariantMap json_map = json_obj.toVariantMap();
       QVector<float> v ; //=  new QVector<float>() ;
       v.push_back(json_map["Time"].toFloat());

       for(QString & col_name : mesure_names){

           v.push_back(json_map[col_name].toFloat());

       }

       topic_model_dic[topic]->addRow(v);
   }


}

void MainWindow::mapInit(){

    const QSize size(400, 400);
    QQuickWidget *w = new QQuickWidget;
    w->resize(size);
    w->setResizeMode(QQuickWidget::SizeRootObjectToView);
    QQmlContext *ctxt = w->rootContext();
    ctxt->setContextProperty("myModel", &m_gps_model);
    w->setSource(QUrl("qrc:/map.qml"));
    ui->mdi->addSubWindow(w);
    w->show();

}

void MainWindow::handleGps(float lat, float lon){

    m_gps_model.insert(new IotConnexion(this->ip_mosquitto,lat,lon));

}

void MainWindow::quitter(){

    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event){

    QMessageBox msgBox(this);
    msgBox.setText("Confirmation");
    msgBox.setInformativeText("Are you closing application?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Yes:
          // Save was clicked
        stopMosquitto();
        event->accept();
          break;
      case QMessageBox::No:
          // Don't Save was clicked
        event->ignore();
          break;
      default:
          // should never be reached
          break;
    }
}


