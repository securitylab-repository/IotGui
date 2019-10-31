#ifndef IOT_CHART_VIEW_H
#define IOT_CHART_VIEW_H

#include <QLineSeries>
#include <QVXYModelMapper>
#include <QChartView>
#include <QChart>
#include <QWidget>
#include <QString>
#include <QVector>

#include "iot_mesures_model.h"

class IotChartView : public QtCharts::QChartView
{
public:
    IotChartView(IotMesuresModel * model = nullptr, int index_mesure = 1 , QWidget * parent = nullptr);

public slots:

    void printGraph(QVector<float> row,QString action);
    void updateGraph(QVector<float> v);
    void prepare(QString) ;

private:
    IotMesuresModel * m_model ;
    QtCharts::QLineSeries *series ;
    QtCharts::QChart *chart ;
    float x_min ;
    float x_max ;
    float y_min ;
    float y_max ;
    int index_mesure_to_show ;

};

#endif // IOT_CHART_VIEW_H
