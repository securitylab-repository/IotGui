#ifndef IOTTREEVIEW_H
#define IOTTREEVIEW_H

#include <QTreeView>
#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QVector>
#include <QString>

#include "iot_mesures_model.h"

class IotTreeView : public QTreeView
{
    Q_OBJECT

public:

    IotTreeView();
    IotTreeView(QWidget* parent);
    IotTreeView(IotMesuresModel * model , QWidget* parent =nullptr , QString topic = "");
    IotTreeView(const IotTreeView &) = delete;
    IotTreeView & operator= (const IotTreeView &) = delete ;
    ~IotTreeView();

private:

    IotMesuresModel * m_model ;
    QString m_topic ;
private slots:

    void openContextMenu(const QPoint &);
    void qmenuActionTriggered(QAction *);

signals:
    void menuActionClicked(QString topic,QString action);

};

#endif // IOTTREEVIEW_H
