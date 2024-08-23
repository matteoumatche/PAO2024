#include "widgettemperatura.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

View::WidgetTemperatura::WidgetTemperatura(Model::Sensore* sensore, QWidget *parent)
    : WidgetGrafico(sensore,parent),
      tempLabel(new QLabel(this)),
      timeSeries(new QLineSeries()),
      tempSeries(new QLineSeries()),
      chart(new QChart()),
      chartView(new QChartView(chart)),
      timeCounter(0) {  // Inizializzazione del contatore del tempo
/*
    QLabel* tempLabel;            // Etichetta per mostrare la temperatura
    QLineSeries *timeSeries;      // Serie di dati per il tempo
    QLineSeries *tempSeries;      // Serie di dati per la temperatura
    QChart *chart;                // Oggetto per il grafico
    QChartView *chartView;        // Oggetto per la visualizzazione del grafico

    int timeCounter;              // Contatore per il tempo (associato ai dati)
*/

    qDebug() << "WidgetTemperatura creato";

    for (int i=0; i<8; i++) {
        sensore->simulaMisura();
        std::map<std::string, std::string> info = sensore->getInfo();
        double dato = std::stod(info["Dato"]); // Converti da stringa a double
        tempSeries->append(1,dato);
    }

    // Aggiungi il grafico al layout
    chart->addSeries(tempSeries);
    chart->addSeries(timeSeries);
    chart->createDefaultAxes();
    chart->setTitle("Grafico Temperatura nel Tempo");

    // Configura gli assi
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Tempo");
    axisX->setLabelFormat("%d");
    axisX->setTickCount(10);  // Numero di etichette sull'asse X
    axisX->setRange(0, 10);   // Imposta il range dell'asse X
    axisX->setMinorTickCount(0);  // Nessun tick minore
    chart->addAxis(axisX, Qt::AlignBottom);
    timeSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Temperatura (°C)");
    axisY->setLabelFormat("%d");
    axisY->setTickCount(8);  // Numero di etichette sull'asse Y
    axisY->setRange(-10, 40);   // Imposta il range dell'asse Y
    axisY->setMinorTickCount(0);  // Nessun tick minore
    chart->addAxis(axisY, Qt::AlignLeft);
    tempSeries->attachAxis(axisY);

    // Configura il QChartView
    chartView->setRenderHint(QPainter::Antialiasing);
    qDebug() << "WidgetTemperatura creato e visualizzato.";

}

void View::WidgetTemperatura::updateData(Model::Temperatura* sensore) {
    tempLabel->setText("Temperatura: " + QString::number(sensore->getDato()) + " °C");
    tempSeries->append(timeCounter++, sensore->getDato());  // Aggiungi il dato al grafico
    qDebug() << "updateData chiamato per WidgetTemperatura.";
}
