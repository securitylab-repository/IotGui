#include "iot_mesures_model.h"
#include <QDebug>
#include <QtCore/QRect>
#include <QtGui/QColor>


void IotMesuresModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}

void IotMesuresModel::addColumn(QString column){

    m_columns.append(column);
    column_index[column] = columnCount() - 1 ;
}

int IotMesuresModel::getIndexOfColumn(QString column) const {

    return column_index[column] ;
}

IotMesuresModel::IotMesuresModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    emit modelReady();
}

QVariant IotMesuresModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return m_columns[section];

     return QVariant();

       // return m_columns[section];

    // FIXME: Implement me!
}

/*bool IotMesuresModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}
*/

int IotMesuresModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

     //qDebug() << "number of rows : " << m_data.count() << "\n";
     return m_data.count();
    // FIXME: Implement me!
}

int IotMesuresModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_columns.count() ;

    // FIXME: Implement me!
}

QVariant IotMesuresModel::data(const QModelIndex &index, int role) const
{

    if(!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole ){

        return m_data[index.row()].at(index.column());

    }
     else if (role == Qt::EditRole ) {

        return m_data[index.row()].at(index.column());

    }
    else if (role == Qt::BackgroundRole) {
           for (const QRect &rect : m_mapping) {
               if (rect.contains(index.column(), index.row()))
                   return QColor(m_mapping.key(rect));
           }
           // cell not mapped return white color
           return QColor(Qt::white);
       }
    // FIXME: Implement me!
    return QVariant();
}

bool IotMesuresModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags IotMesuresModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);

    //return Qt::ItemIsEditable; // FIXME: Implement me!
}
/*
bool IotMesuresModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}
*/
void IotMesuresModel::addRow(QVector<float>  row){

    beginInsertRows(QModelIndex(), 0, 0);
    m_data.append(row);
    endInsertRows();
    emit modelchanged(row);
}
QVector<float> IotMesuresModel::getRow(int index) const {

    return this->m_data.at(index);

}

QString IotMesuresModel::getColumn(int index) const {

    return m_columns[index] ;
}



/*bool IotMesuresModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
}

bool IotMesuresModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!

    endRemoveRows();
}

bool IotMesuresModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
}
*/
