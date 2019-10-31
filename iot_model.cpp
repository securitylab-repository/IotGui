#include "iot_model.h"

int Model::rowCount(const QModelIndex&) const {
  return mItems.size();
}

QVariant Model::data(const QModelIndex& index, int role) const {
 // QObject* item = mItems.at(index.row());
  IotConnexion* item = (IotConnexion*) mItems.at(index.row());

  switch (role) {

  case Roles::IPRole:
    return item->getIP();
  case Roles::LongitudeRole:
    return item->getLongitude();
  case Roles::LatitudeRole:
      return item->getLatitude() ;
  default:
  return QVariant();
  }

  //return QVariant::fromValue(item);
}

void Model::insert(QObject* item) {
  beginInsertRows(QModelIndex(), 0, 0);
  mItems.push_front(item);
  endInsertRows();
}

void Model::remove(QObject* item) {
  for (int i = 0; i < mItems.size(); ++i) {
    if (mItems.at(i) == item) {
      beginRemoveRows(QModelIndex(), i, i);
      mItems.remove(i);
      endRemoveRows();
      break;
    }
  }
}

QHash<int, QByteArray> Model::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Roles::IPRole] = "ip";
  roles[Roles::LongitudeRole] = "longitude";
  roles[Roles::LatitudeRole] = "latitude";
  return roles;
}
