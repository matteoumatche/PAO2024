#ifndef WIDGETTEMPERATURA_H
#define WIDGETTEMPERATURA_H
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QBarSeries>
#include "../Model/temperatura.h"  // Includi il modello specifico di Temperatura
#include "widgetgrafico.h"

namespace View{
class WidgetTemperatura : public WidgetGrafico {
    Q_OBJECT
public slots:
    void simulazione(Model::Sensore* sensore) override;
public:
    explicit WidgetTemperatura(Model::Sensore* sensore, QWidget *parent = nullptr);
    QBarSeries graficoTemperatura;

private:
    QLabel* tempLabel;            // Etichetta per mostrare la temperatura

};
}
#endif // WIDGETTEMPERATURA_H
