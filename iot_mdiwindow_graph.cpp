#include "iot_mdiwindow_graph.h"


IotMdiWindowGraph::IotMdiWindowGraph(QWidget * parent, QString winname): IotMdiWindow(parent,winname)
{

}


void IotMdiWindowGraph::prepareWindow(){

 emit newMdiWindowAdded(this) ;

}
