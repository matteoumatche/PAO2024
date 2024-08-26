#ifndef WIDGETTEMPERATURA_H
#define WIDGETTEMPERATURA_H

#include "../Model/temperatura.h"
#include "widgetgrafico.h"

#include <QLabel>
#include <QBarSeries>

namespace View{

class WidgetTemperatura : public WidgetGrafico {
    Q_OBJECT
public slots:
    void simulazione(Model::Sensore* sensore) override;
public:
    explicit WidgetTemperatura(Model::Sensore* sensore, QWidget *parent = nullptr);
    void updateData(Model::Temperatura* sensore);
    QBarSeries graficoTemperatura;

private:
    QLabel* tempLabel;
};

}

#endif
