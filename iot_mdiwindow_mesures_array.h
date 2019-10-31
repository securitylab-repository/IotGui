#ifndef IOT_MESURES_ARRAY_H
#define IOT_MESURES_ARRAY_H

#include "iot_mdiwindow.h"

class IotMdiWindowMesuresArray : public IotMdiWindow
{

public:

    IotMdiWindowMesuresArray(QWidget * parent = nullptr ,  QString winname = "Mesures");
    void prepareWindow() ;



};

#endif // IOT_MESURES_ARRAY_H
