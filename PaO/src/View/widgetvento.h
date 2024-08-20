#ifndef WIDGETVENTO_H
#define WIDGETVENTO_H
#include <QWidget>
#include "widgetgrafico.h"
namespace View{
class WidgetVento : public WidgetGrafico {
    Q_OBJECT
public:
    explicit WidgetVento(Model::Sensore* s,QWidget *parent = nullptr);
public slots:
    void simulazione() override ;
};
}
#endif // WIDGETVENTO_H
