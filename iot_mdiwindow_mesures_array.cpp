#include "iot_mdiwindow_mesures_array.h"


IotMdiWindowMesuresArray::IotMdiWindowMesuresArray(QWidget * parent, QString winname): IotMdiWindow(parent,winname)
{

}


void IotMdiWindowMesuresArray::prepareWindow() {

    emit newMdiWindowAdded(this) ;

}
