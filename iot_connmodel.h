#ifndef IOT_CONN_MODEL_H
#define IOT_CONN_MODEL_H

#include <QString>
#include <QVector>
#include <QtCore>

#include <QAbstractItemModel>
#include "iot_connexion.h"
class IotConnModel : public QObject

{

    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel* connexions READ getConnexions)

    public:

        explicit IotConnModel();

        QAbstractItemModel *getConnexions() const;
        void setConnexions(QAbstractItemModel *connexions);
        void updateModel(IotConnexion conn);

    private:

        QAbstractItemModel * m_connexions ;
};





#endif // IOT_CONN_MODEL_H
