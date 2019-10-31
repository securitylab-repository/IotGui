#include "iot_connmodel.h"
# include <QStandardItemModel>

QAbstractItemModel *IotConnModel::getConnexions() const
{
    return m_connexions;
}

void IotConnModel::setConnexions(QAbstractItemModel *connexions)
{
    m_connexions = connexions;
}


IotConnModel::IotConnModel()
   {
       m_connexions=new QStandardItemModel();
       m_connexions->insertColumn(0);
   }


void IotConnModel::updateModel(IotConnexion conn)
{

    const int newRow= m_connexions->rowCount();
    m_connexions->insertRow(newRow);
    m_connexions->setData(m_connexions->index(newRow,0),QVariant::fromValue(conn),Qt::EditRole);
}

