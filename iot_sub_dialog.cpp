#include "iot_sub_dialog.h"

#include <ui_iot_sub_dialog.h>
#include <QDebug>

#include <regex>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>


void split(const std::string& str, QVector<QString>& cont, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {

        QString t(token.c_str());
        cont.push_back(t);
    }
}

IotSubDialog::IotSubDialog(QWidget * parent, QString winname) : QDialog (parent) , di(new Ui::SubDialog)

{
    di->setupUi(this) ;
     this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle(winname) ;

}

IotSubDialog::~IotSubDialog(){

    delete di ;
}


void IotSubDialog::on_ok_button_clicked()
{


  //  std::regex mesure_format("[a-z,A-Z,0-9]+,[a-Z,a-z,0-9]*,*");

   // if ( ! std::regex_match(di->mesures_edit->toPlainText().toStdString(),mesure_format)){


   // }

    std::string mesures_coma(di->mesures_edit->toPlainText().toStdString());
    QVector<QString> mesures ;
    split(mesures_coma,mesures,',');

    emit topicMesureNames(di->topic_edit->text(),mesures);
    this->close();

}

void IotSubDialog::on_cancel_button_clicked()
{
    this->close();
}
