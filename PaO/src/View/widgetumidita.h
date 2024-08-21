#ifndef WIDGETUMIDITA_H
#define WIDGETUMIDITA_H
#include <QWidget>
#include "widgetgrafico.h"

namespace View{
class WidgetUmidita : public WidgetGrafico {
    Q_OBJECT
public:
    explicit WidgetUmidita(Model::Sensore* s,QWidget *parent = nullptr);
    void updateData(/* data specific to wind sensor */);
};
}
#endif // WIDGETUMIDITA_H
