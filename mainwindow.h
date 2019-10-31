#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include "iot_connexion.h"
#include <QList>
#include "iot_model.h"
#include "iot_mesures_model.h"
#include <QVXYModelMapper>
#include <QLineSeries>
#include <QtNetwork>
#include <QChart>
#include <QChartView>
#include "iot_mosquitto.h"
#include "iot_mdiwindow_graph.h"
#include <memory>

#include <QStringList>

#include <QVector>
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~ MainWindow();
    void mapInit();
    void handleGps(float,float);

    void closeEvent(QCloseEvent *) ;
public slots:

    void handleMosqConnected();
    void handleMosqMsg(QString,QString);
    void handleMosqStoped();
    void mosquitoConnect(QString,int);
    void mosquitoNotConnected(QString);
    void handleSubscribe(QString,QVector<QString>);
    void deleteSubscribe(QVector<QString>);

    void printGraph(QString,QString);
    void printMosquittoConnDialog();
    void printMosquittoSubDialog();
    void printMosquittoDelSubDialog();
    void stopMosquitto();
    void printTabMesures(QWidget *);
    void quitter();

signals:
    void start_mosquitto_sig();

private:
    Ui::MainWindow *ui;
    QThread mqttThread;
    Model  m_gps_model ;
    IotMosquitto *  mosq {nullptr} ;
    QVector<QString> mesure_names ;
    QHash<QString,IotMesuresModel*> topic_model_dic ;
    QHash<QString,IotMdiWindow*> topic_mdiwindow_dic ;
    QHash<QString,QAction*> topic_action_dic ;
    QHash<QString,IotMdiWindow*> topic_metric_graph_dic ;

    QStringList subscribed_topics_list ;

    QMenu * mesures_submenu ;
    QString ip_mosquitto ;
};

#endif // MAINWINDOW_H
