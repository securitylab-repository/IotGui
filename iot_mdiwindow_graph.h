#ifndef IOT_MDIWINDOW_GRAPH_H
#define IOT_MDIWINDOW_GRAPH_H


#include "iot_mdiwindow.h"

class IotMdiWindowGraph : public IotMdiWindow
{
public:
    IotMdiWindowGraph(QWidget * parent = nullptr, QString winname= "Graph" );
    void prepareWindow() ;
};

#endif // IOT_MDIWINDOW_GRAPH_H
