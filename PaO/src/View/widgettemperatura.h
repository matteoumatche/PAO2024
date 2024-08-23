#ifndef WIDGETTEMPERATURA_H
#define WIDGETTEMPERATURA_H
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QLabel>
#include <QWidget>
#include "../Model/temperatura.h"  // Includi il modello specifico di Temperatura
#include "widgetgrafico.h"

namespace View{
class WidgetTemperatura : public WidgetGrafico {
    Q_OBJECT
public:
    explicit WidgetTemperatura(Model::Sensore* sensore, QWidget *parent = nullptr);
    void updateData(Model::Temperatura* sensore);  // Ora accetta direttamente un sensore di tipo Temperatura

private:
    QLabel* tempLabel;            // Etichetta per mostrare la temperatura
    QLineSeries *timeSeries;      // Serie di dati per il tempo
    QLineSeries *tempSeries;      // Serie di dati per la temperatura
    QChart *chart;                // Oggetto per il grafico
    QChartView *chartView;        // Oggetto per la visualizzazione del grafico

    int timeCounter;              // Contatore per il tempo (associato ai dati)

};
}
#endif // WIDGETTEMPERATURA_H
