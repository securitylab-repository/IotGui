#ifndef IOT_MDIWINDOW_H
#define IOT_MDIWINDOW_H

#include <QMdiSubWindow>
#include <QString>
#include <QCloseEvent>
#include <QMdiSubWindow>
#include <QObject>
#include <QWidget>

class IotMdiWindow : public QMdiSubWindow
{

    Q_OBJECT

public:
    ~IotMdiWindow();
    IotMdiWindow(QWidget * parent = nullptr);
    IotMdiWindow(QWidget * parent = nullptr, QString winname="MdiSubWindow");
    void addWidget(QWidget*);
    void closeEvent(QCloseEvent*);
    virtual void prepareWindow() = 0 ;

signals :
    void newMdiWindowAdded(QWidget*);
    void mdiWindowClosed();

private:
    QString m_winname ;
    QWidget * centralWidget ;
};

#endif // IOT_MDIWINDOW_H
