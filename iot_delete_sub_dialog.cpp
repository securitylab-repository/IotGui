#include "iot_delete_sub_dialog.h"

#include <ui_iot_delete_sub_dialog.h>
#include <QDebug>



IotDelSubDialog::IotDelSubDialog(QWidget * parent, QStringList list_topics) : QDialog (parent) , di(new Ui::DelSubDialog)

{
    di->setupUi(this) ;
    this->setAttribute(Qt::WA_DeleteOnClose);
    _model.setStringList(list_topics);
    di->listView->setModel(&_model);
}

IotDelSubDialog::~IotDelSubDialog(){

    delete di ;
}


void IotDelSubDialog::on_ok_button_clicked()
{
    emit topicDeleted(deleted_topics);
    this->close();

}

void IotDelSubDialog::on_cancel_button_clicked()
{
    this->close();
}

void IotDelSubDialog::on_delete_button_clicked()
{
    if (di->listView->currentIndex().data().toString() == "")
        return ;

    deleted_topics.push_back( di->listView->currentIndex().data().toString());
    qDebug() <<  di->listView->currentIndex().data().toString() << "\n" ;
    _model.removeRows(di->listView->currentIndex().row(),1);

}

