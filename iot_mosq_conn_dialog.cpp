#include "iot_mosq_conn_dialog.h"
#include <ui_iot_mosq_connection_dialog.h>
#include <QDebug>

#include <regex>
#include <string>
#include <QMessageBox>

IotMosqConnDialog::IotMosqConnDialog(QWidget * parent, QString winname) : QDialog (parent) , di(new Ui::Dialog)

{

    di->setupUi(this) ;
    this->setWindowTitle(winname) ;
    this->setAttribute(Qt::WA_DeleteOnClose);
}

IotMosqConnDialog::~IotMosqConnDialog(){

    delete di ;
}



void IotMosqConnDialog::on_pushButton_clicked()
{

    std::regex iprgx("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    std::regex portrgx("[0-9]+");
    QMessageBox * msgBox = nullptr ;

    std::string ip_server(di->lineEdit->text().toStdString());
    if ( ! std::regex_match(ip_server,iprgx)){

        QMessageBox * msgBox = new QMessageBox(this);
        msgBox->setText("Invalid format of IP");
        msgBox->setWindowTitle("Error Message");
        msgBox->exec();
    }
    else{

        emit ipPort(di->lineEdit->text(),di->spinBox->value());
        this->close();
    }

    if(!msgBox)
        delete msgBox ;

}

void IotMosqConnDialog::on_pushButton_2_clicked()
{
   this->close();
}
