#include "iot_mdiwindow.h"
#include <QDebug>

IotMdiWindow::~IotMdiWindow() {

    qDebug() << Q_FUNC_INFO << m_winname << "\n" ;
    delete centralWidget ;

}

IotMdiWindow::IotMdiWindow(QWidget * parent): QMdiSubWindow(parent)
{

}

IotMdiWindow::IotMdiWindow(QWidget * parent, QString winname) : QMdiSubWindow(parent), m_winname(winname)
{

    this->setWindowTitle(m_winname);
}

void IotMdiWindow::addWidget(QWidget * widget) {

    centralWidget = widget ;
    this->setWidget(widget);
   // widget->show();
}

void IotMdiWindow::closeEvent(QCloseEvent * event){


    emit mdiWindowClosed();
    event->accept();
}
