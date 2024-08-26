#ifndef WIDGETFOTOCELLULA_H
#define WIDGETFOTOCELLULA_H

#include "widgetgrafico.h"
#include "../Model/sensore.h"

namespace View{

class WidgetFotocellula : public WidgetGrafico {
    Q_OBJECT

public:
    explicit WidgetFotocellula(Model::Sensore* s, QWidget *parent = nullptr);
    void updateData(/* data specific to wind sensor */);
};

}

#endif
