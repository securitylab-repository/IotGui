#ifndef IOTMESURESMODEL_H
#define IOTMESURESMODEL_H

#include <QList>
#include <QVector>

#include <QAbstractTableModel>

#include <QtCore/QHash>
#include <QtCore/QRect>

class IotMesuresModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit IotMesuresModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

 //  bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;

   Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
  //  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  //  bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
 //   bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  //  bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    void addRow(QVector<float>);
    void addColumn(QString);
    void addMapping(QString color, QRect area);
    void clearMapping() { m_mapping.clear(); }
    QVector<float>  getRow(int index) const;
    QString getColumn(int index) const ;
    int getIndexOfColumn(QString column) const ;
signals:

    void modelReady();
    void modelchanged(QVector<float>);


private:

    QList<QVector<float>> m_data ;
    QList<QString> m_columns ;
    int m_columnCount;
    int m_rowCount;
    QHash<QString, QRect> m_mapping;
    QHash<QString,int> column_index ;


};
#endif // IOTMESURESMODEL_H
