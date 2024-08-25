#include "widgettemperatura.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QBarSeries>
#include <QRandomGenerator>
#include <QBarSet>
#include <QChart>

View::WidgetTemperatura::WidgetTemperatura(Model::Sensore* sensore, QWidget *parent)
    : WidgetGrafico(parent)
{
/*
    QLabel* tempLabel;            // Etichetta per mostrare la temperatura
    QLineSeries *timeSeries;      // Serie di dati per il tempo
    QLineSeries *tempSeries;      // Serie di dati per la temperatura
    QChart *chart;                // Oggetto per il grafico
    QChartView *chartView;        // Oggetto per la visualizzazione del grafico

    int timeCounter;              // Contatore per il tempo (associato ai dati)
*/
    QBarSet *set = new QBarSet("Prova");

    for (int i = 0; i < 10; ++i) {
        int randomValue = QRandomGenerator::global()->bounded(0, 40);
        *set << randomValue;  // Aggiungi il valore randomico al set
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);

    qDebug() << "WidgetTemperatura creato";



    /*
    for (int i=0; i<8; i++) {
        sensore->simulaMisura();
        std::map<std::string, std::string> info = sensore->getInfo();
        double dato = std::stod(info["Dato"]); // Converti da stringa a double
        tempSeries->append(1,dato);
    }*/

}

void View::WidgetTemperatura::updateData(Model::Temperatura* sensore) {
    qDebug() << "updateData chiamato per WidgetTemperatura.";
}
