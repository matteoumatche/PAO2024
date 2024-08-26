#ifndef WIDGETTEMPERCEPITA_H
#define WIDGETTEMPERCEPITA_H

#include "widgetgrafico.h"
#include "../Model/Sensore.h"
namespace View{

class WidgetTempercepita : public WidgetGrafico{

public:
    explicit WidgetTempercepita(Model::Sensore* s,QWidget *parent );
    void simulazione(Model::Sensore*) override;
};

}

#endif
