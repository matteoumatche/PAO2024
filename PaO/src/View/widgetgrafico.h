#ifndef WIDGETGRAFICO_H
#define WIDGETGRAFICO_H

#include <QWidget>
#include "src/Model/sensore.h"
namespace View{
class WidgetGrafico : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetGrafico(Model::Sensore* s,QWidget *parent = nullptr);
signals:
public slots:
    virtual void simulazione();
    //virtual void valoreMisura();
};
}
#endif // WIDGETGRAFICO_H
