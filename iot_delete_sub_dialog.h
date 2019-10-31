#ifndef IOT_DELETE_SUB_DEIALOG_H
#define IOT_DELETE_SUB_DEIALOG_H

#include <QDialog>
#include <QObject>
#include <QVector>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class DelSubDialog;
}

class IotDelSubDialog : public QDialog
{
    Q_OBJECT
public:
    IotDelSubDialog(QWidget * parent , QStringList);
    ~IotDelSubDialog();

private slots:

    void on_ok_button_clicked();
    void on_cancel_button_clicked();
    void on_delete_button_clicked();

signals :

    void topicDeleted(QVector<QString>);

private :

    Ui::DelSubDialog * di ;
    QStringListModel _model ;
    QVector<QString> deleted_topics ;
};

#endif // IOT_DELETE_SUB_DEIALOG_H
