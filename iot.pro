#-------------------------------------------------
#
# Project created by QtCreator 2019-03-08T17:23:12
#
#-------------------------------------------------

QT       += core gui network quickwidgets positioning concurrent charts
requires(qtConfig(tableview))

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    iot_chart_view.cpp \
    iot_delete_sub_dialog.cpp \
    iot_mdiwindow.cpp \
    iot_mdiwindow_graph.cpp \
    iot_mdiwindow_mesures_array.cpp \
    iot_mosq_conn_dialog.cpp \
    iot_sub_dialog.cpp \
    iot_treeview.cpp \
        mainwindow.cpp \
    iot_connexion.cpp \
    iot_model.cpp \
    iot_mosquitto.cpp \
    iot_mesures_model.cpp \
    static_signal.cpp

HEADERS  += mainwindow.h \
    iot_chart_view.h \
    iot_delete_sub_dialog.h \
    iot_mdiwindow.h \
    iot_mdiwindow_graph.h \
    iot_mdiwindow_mesures_array.h \
    iot_mosq_conn_dialog.h \
    iot_sub_dialog.h \
    iot_treeview.h \
    iot_connexion.h \
    iot_model.h \
    iot_mosquitto.h \
    iot_mesures_model.h \
    static_signal.h

FORMS    += mainwindow.ui \
    iot_delete_sub_dialog.ui \
    iot_mosq_connection_dialog.ui \
    iot_sub_dialog.ui

RESOURCES += qml.qrc
#DISTFILES += \
 #   map.qml

LIBS += -lmosquitto
