#ifndef WIDGETFOTOCELLULA_H
#define WIDGETFOTOCELLULA_H

#include "widgetgrafico.h"
#include "../Model/sensore.h"

namespace View{

class WidgetFotocellula : public WidgetGrafico {
    Q_OBJECT
private:
    std::vector<Model::Sensore*>* sensori;
public:
    explicit WidgetFotocellula(std::vector<Model::Sensore*>* s, QWidget *parent = nullptr);
    void simulazione(Model::Sensore*) override;
};

}

#endif
