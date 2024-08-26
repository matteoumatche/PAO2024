#ifndef WIDGETTEMPERCEPITA_H
#define WIDGETTEMPERCEPITA_H

#include "widgetgrafico.h"
<<<<<<< HEAD
#include "../Model/Sensore.h"
=======
#include "src/Model/sensore.h"

>>>>>>> 0cfb30eb57fb2a5115f3011dd6bb8e125d12ce5b
namespace View{

class WidgetTempercepita : public WidgetGrafico{

public:
    explicit WidgetTempercepita(Model::Sensore* s,QWidget *parent );
<<<<<<< HEAD
    void simulazione(Model::Sensore*) override;
=======
    void updateData(/* data specific to temperature sensor */);

>>>>>>> 0cfb30eb57fb2a5115f3011dd6bb8e125d12ce5b
};

}

#endif
