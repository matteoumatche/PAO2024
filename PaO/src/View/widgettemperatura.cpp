#include "widgettemperatura.h"
#include <QVBoxLayout>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>

View::WidgetTemperatura::WidgetTemperatura(Model::Sensore* sensore, QWidget *parent)
    : WidgetGrafico(parent)
{
/*
    QBarSet *set = new QBarSet("Prova");

    for (int i = 0; i < 10; ++i) {
        sensore->simulaMisura();  // Simula una misura
        std::map<std::string, std::string> info = sensore->getInfo();  // Ottieni le informazioni dal sensore
        double dato = std::stod(info["Dato"]);  // Converti il valore "Dato" da stringa a double
        *set << dato;  // Aggiungi il valore al set
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);

    QStringList categories;
    categories << "9-10" << "10-11" << "11-12" << "12-13" << "13-14" << "14-15" << "15-16" << "16-17" << "17-18" << "18-19";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(-10,40);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    qDebug() << "WidgetTemperatura creato";

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);

    setLayout(layout);

    //
    for (int i=0; i<8; i++) {
        sensore->simulaMisura();
        std::map<std::string, std::string> info = sensore->getInfo();
        double dato = std::stod(info["Dato"]); // Converti da stringa a double
        tempSeries->append(1,dato);
    }*/

}

void View::WidgetTemperatura::simulazione(Model::Sensore* sensore) {
    qDebug() << "updateData chiamato per WidgetTemperatura.";
    delete layout();

    QBarSet *set = new QBarSet("Prova");

    for (int i = 0; i < 10; ++i) {
        sensore->simulaMisura();  //simula una misura
        std::map<std::string, std::string> info = sensore->getInfo();  //ottiene le informazioni dal sensore
        double dato = std::stod(info["Dato"]);  //conversione "Dato" da stringa a double
        *set << dato;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);

    QStringList categories;
    categories << "9-10" << "10-11" << "11-12" << "12-13" << "13-14" << "14-15" << "15-16" << "16-17" << "17-18" << "18-19";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(-10,40);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    qDebug() << "WidgetTemperatura creato";

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);

    setLayout(layout);

}
