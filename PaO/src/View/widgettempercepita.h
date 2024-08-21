#ifndef WIDGETTEMPERCEPITA_H
#define WIDGETTEMPERCEPITA_H
#include <QWidget>
#include "widgetgrafico.h"
namespace View{
class WidgetTempercepita : public WidgetGrafico{
public:
    explicit WidgetTempercepita(Model::Sensore* s,QWidget *parent );
    void updateData(/* data specific to temperature sensor */);
};
}
#endif // WIDGETTEMPERCEPITA_H
