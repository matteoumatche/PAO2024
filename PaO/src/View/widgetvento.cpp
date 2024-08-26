#include "widgetvento.h"
#include "../Model/vento.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QPen>
#include <QPair>
#include <QValueAxis>
#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QLineSeries>


//QT_CHARTS_USE_NAMESPACE

View::WidgetVento::WidgetVento(Model::Sensore* s, QWidget* parent)
    : WidgetGrafico(parent), vento(static_cast<Model::Vento*>(s)), mostraGrafico(false) {
/*
    // Create the chart and series
    chart = new QChart();
    series = new QLineSeries();
    chart->addSeries(series);

    // Configure the chart's axes
    //chart->axisX()->setTitleText("Time");
    //chart->axisY()->setTitleText("Speed");



    // Use a QDateTimeAxis for time-based x-axis
    QDateTimeAxis* axisX = new QDateTimeAxis;
    axisX->setTitleText("ora misurazione");
    axisX->setFormat("hh:mm:ss");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Use a QValueAxis for speed-based y-axis
    QValueAxis* axisY = new QValueAxis;
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Velocità");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(rect()); // Ensure the chart view fills the widget

    // Create a layout to hold the chart view
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);*/
}

void View::WidgetVento::simulazione(Model::Sensore* s) {
    /*datiSimulati.clear();
    QDateTime currentTime = QDateTime::currentDateTime();
    for (int i = 0; i < 10; ++i) {
        vento->simulaMisura();
        auto dato = vento->getDato();
        datiSimulati[currentTime.addSecs(i)] = dato; // Use time increments
        qDebug() << "Time:" << currentTime.addSecs(i).toString() << "Speed:" << dato.first;
    }

    // pulizia
    series->clear();

    chartView->setGeometry(rect()); // Ensure the chart view fills the widget
    chartView->update(); // Refresh the chart view

    mostraGrafico = true;
    update();  // Trigger for the repaint
    */
}

void View::WidgetVento::paintEvent(QPaintEvent* event) {
    /*QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (mostraGrafico) {
        for (auto it = datiSimulati.begin(); it != datiSimulati.end(); ++it) {
            double x = it.key().toMSecsSinceEpoch(); // Convert time to milliseconds
            double y = it.value().first; // Speed
            series->append(x, y);
        }
        // Let the chart handle the drawing

        chartView->update();
        chartView->setGeometry(rect()); // Ensure the chart view fills the widget

    } else {
        // Modalità bussola
        auto windData = vento->getDato();
        double velocita = windData.first;
        double angolo = windData.second;

        int larghezza = this->width();
        int altezza = this->height();
        QPoint centro(larghezza / 2, altezza / 2);

        int raggio = std::min(larghezza, altezza) / 2 - 10;
        painter.setPen(Qt::black);
        painter.drawEllipse(centro, raggio, raggio);

        double angoloRad = qDegreesToRadians(angolo);
        QPoint puntoFinale(centro.x() + raggio * std::cos(angoloRad) * (velocita / vento->getMaxVelocita()),
                           centro.y() - raggio * std::sin(angoloRad) * (velocita / vento->getMaxVelocita()));

        QPen penna(Qt::red, 2);
        painter.setPen(penna);
        painter.drawLine(centro, puntoFinale);
    }*/
}
