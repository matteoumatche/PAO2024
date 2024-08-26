#include "widgetumidita.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSplineSeries>
#include <QChart>
#include <QValueAxis>
#include <QChartView>

View::WidgetUmidita::WidgetUmidita(Model::Sensore* s, QWidget *parent)
    : WidgetGrafico(parent) {
    /*
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Dati del sensore Umidità", this);
    layout->addWidget(label);

    setLayout(layout);
    */
}

void View::WidgetUmidita::simulazione(Model::Sensore* sensore) {
    qDebug() << "simulazione chiamato per WidgetUmidita.";

    if (QLayout* oldLayout = layout()) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();  // Rimuove i widget figli
            delete item;  // Rimuove il layout item
        }
        delete oldLayout;
    }

    QSplineSeries *series = new QSplineSeries();
    series->setName("spline");

    for (int i = 0; i < 24; ++i) {
        sensore->simulaMisura();  //simula una misura
        std::map<std::string, std::string> info = sensore->getInfo();  //ottiene le informazioni dal sensore
        double dato = std::stod(info["Dato"]);  //conversione "Dato" da stringa a double
        series->append(i, dato);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Andamento umidità giornaliera");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 100);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}
