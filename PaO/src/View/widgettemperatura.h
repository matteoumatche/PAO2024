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
public:
    explicit WidgetTemperatura(Model::Sensore* sensore, QWidget *parent = nullptr);
    void updateData(Model::Temperatura* sensore);  // Ora accetta direttamente un sensore di tipo Temperatura
    QBarSeries graficoTemperatura;

private:
    QLabel* tempLabel;            // Etichetta per mostrare la temperatura

};
}
#endif // WIDGETTEMPERATURA_H
