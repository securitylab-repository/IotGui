#ifndef IOT_MOSQ_CONN_DIALOG_H
#define IOT_MOSQ_CONN_DIALOG_H

#include <QDialog>
#include <QObject>

namespace Ui {
class Dialog;
}

class IotMosqConnDialog : public QDialog
{
    Q_OBJECT
public:
    IotMosqConnDialog(QWidget * parent = nullptr , QString winname = "Mosquitto Subcribe");
    ~IotMosqConnDialog();

private slots:



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals :

    void ipPort(QString,int);

private :

    Ui::Dialog * di ;

};


#endif // IOT_MOSQ_CONN_DIALOG_H
