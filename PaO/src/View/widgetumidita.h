#ifndef WIDGETUMIDITA_H
#define WIDGETUMIDITA_H

#include "widgetgrafico.h"
#include "src/Model/sensore.h"

namespace View{

class WidgetUmidita : public WidgetGrafico {
    Q_OBJECT

public:
    explicit WidgetUmidita(Model::Sensore* s,QWidget *parent = nullptr);
    void updateData(/* data specific to wind sensor */);
};

}

#endif
