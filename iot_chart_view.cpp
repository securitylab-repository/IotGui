#include "iot_chart_view.h"
#include <QDebug>

using namespace QtCharts;


IotChartView::IotChartView(IotMesuresModel * model , int index_mesure, QWidget * parent): QChartView (parent) , m_model(model),x_min(0),x_max(120), y_min(0), y_max(50){

    //QVXYModelMapper *mapper = nullptr ;

    index_mesure_to_show = index_mesure;

    chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);
    series = new QLineSeries;
    series->setName(m_model->getColumn(index_mesure));

    //mapper = new QVXYModelMapper(this);
    //mapper->setXColumn(0);
    //mapper->setYColumn(1);
    //mapper->setSeries(series);
    //mapper->setModel(m_model);
    connect(m_model,&IotMesuresModel::modelchanged,this,&IotChartView::updateGraph);
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, 100);
    chart->axes(Qt::Vertical).first()->setRange(0, 0);
    this->setChart(chart);
    this->setRenderHint(QPainter::Antialiasing);
    this->setMinimumSize(640, 480);
    // for storing color hex from the series
    //QString seriesColorHex = "#000000";
    // get the color of the series and use it for showing the mapped area
    //seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    //m_model->addMapping(seriesColorHex, QRect(0, 0, 2, m_model->rowCount()));

    for (int i =0; i < m_model->rowCount() ; i++)

        updateGraph(m_model->getRow(i));

}

void IotChartView::prepare(QString column_name) {

    index_mesure_to_show =  m_model->getIndexOfColumn(column_name)  ;


}

void IotChartView::updateGraph(QVector<float> v){


    if (v.at(0) < x_min)
        x_min = v.at(0);

    if (v.at(0) > x_max)
       x_max = v.at(0);

     if (v.at(index_mesure_to_show) < y_min)
        y_min = v.at(index_mesure_to_show);

    if (v.at(index_mesure_to_show) > y_max)
        y_max = v.at(index_mesure_to_show);


    chart->axes(Qt::Vertical).first()->setRange(y_min, y_max);
    chart->axes(Qt::Horizontal).first()->setRange(x_min,x_max);

    series->append(v.at(0),v.at(index_mesure_to_show));
    this->repaint();
}

void IotChartView::printGraph(QVector<float> row,QString action) {

    qDebug() << "printGraph" << row << action << "\n" ;
    this->show();

}
