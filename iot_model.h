#ifndef IOT_MODEL_H
#define IOT_MODEL_H
#include <QAbstractListModel>
#include <QVector>
#include "iot_connexion.h"

class Model : public QAbstractListModel {
  Q_OBJECT
public:
    enum Roles {
    IPRole = Qt::UserRole + 1,
    LongitudeRole,
    LatitudeRole
    };
    
  int rowCount(const QModelIndex&) const override;
  QVariant data(const QModelIndex& index, int role) const override;

public slots:
  void insert(QObject* item);
  void remove(QObject* item);

protected:
  QHash<int, QByteArray> roleNames() const override;

private:
  QVector<QObject*> mItems;
};
#endif // IOT_MODEL_H
