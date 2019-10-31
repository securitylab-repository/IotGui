#include "iot_treeview.h"

#include <QMenu>
#include <QAction>
#include <QDebug>



IotTreeView::IotTreeView(): QTreeView ()
{

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&IotTreeView::customContextMenuRequested,this,&IotTreeView::openContextMenu);

}

IotTreeView::IotTreeView(QWidget * parent): QTreeView (parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&IotTreeView::customContextMenuRequested,this,&IotTreeView::openContextMenu);

}


IotTreeView::IotTreeView(IotMesuresModel * model, QWidget * parent, QString topic): QTreeView (parent),m_model(model),m_topic(topic)
{

    this->setModel(m_model);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&IotTreeView::customContextMenuRequested,this,&IotTreeView::openContextMenu);
}


IotTreeView::~IotTreeView()
{

    // don't delete m_model, it can be used by another object

}

void IotTreeView::openContextMenu(const QPoint & position){

    QMenu menu ;
    connect(&menu,&QMenu::triggered, this, &IotTreeView::qmenuActionTriggered);
    for (int i = 1 ; i < m_model->columnCount() ; i++){

        menu.addAction(m_model->getColumn(i));
    }

    menu.exec(this->viewport()->mapToGlobal(position));
}

void IotTreeView::qmenuActionTriggered(QAction * action){

    qDebug() << "IotTreeView::qmenuActionTriggered" << action->text() << "\n" ;
    emit  menuActionClicked(m_topic,action->text());
/*
    if(indexes.length() > 0 ){

        QModelIndex indexSelected = indexes.at(0);
        qDebug() << "row" << this->m_model->getRow(indexSelected.row()) << action->text() << "\n";
        emit  menuActionClicked(this->m_model->getRow(indexSelected.row()),action->text());
    }*/
}
