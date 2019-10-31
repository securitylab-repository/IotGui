#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QObject>

namespace Ui {
class SubDialog;
}

class IotSubDialog : public QDialog
{
    Q_OBJECT
public:
    IotSubDialog(QWidget * parent = nullptr , QString winname = "Mosquitto Subcribe");
    ~IotSubDialog();

private slots:

    void on_ok_button_clicked();
    void on_cancel_button_clicked();

signals :

    void topicMesureNames(QString,QVector<QString>);

private :

    Ui::SubDialog * di ;

};

#endif // DIALOG_H
