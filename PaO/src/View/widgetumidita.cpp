#include "widgetumidita.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QValueAxis>
#include <QSplitter>

View::WidgetUmidita::WidgetUmidita(Model::Sensore* s, QWidget *parent)
    : WidgetGrafico(parent),
      chart(new QChart()),
      chartView(new QChartView(chart)),
      tabella(new QTableWidget(0, 2, this)),
      series(new QSplineSeries())
{
    // Configure table
    tabella->setHorizontalHeaderLabels(QStringList() << "misura" << "umidità relativa (%)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    // Configure chart
    chart->legend()->hide();
    series->setName("spline");
    chart->addSeries(series);
    chart->setTitle("Andamento umidità giornaliera");

    // Configure axes
    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%d");  // Display integer values on the x-axis
    axisX->setTitleText("Ora");
    axisX->setRange(0, 24);  // Set range from 0 to 24

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Umidità (%)");
    axisY->setRange(0, 100);  // Set range for the y-axis

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chartView->setRenderHint(QPainter::Antialiasing);

    // Create a QSplitter to manage the layout
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(chartView);
    splitter->addWidget(tabella);

    // Set the initial sizes for the splitter
    splitter->setSizes(QList<int>() << 2 * 100 << 100);  // 2/3 for chart, 1/3 for table

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

    /* Layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(chartView);
    layout->addWidget(tabella);
    setLayout(layout);*/
}

void View::WidgetUmidita::simulazione(Model::Sensore* sensore) {
    // Clear the series and table
    series->clear();
    tabella->setRowCount(0);

    for (int i = 0; i < 24; ++i) {
        sensore->simulaMisura();  // Simula una misura
        std::map<std::string, std::string> info = sensore->getInfo();  // Ottiene le informazioni dal sensore
        double dato = std::stod(info["Dato"]);  // Conversione "Dato" da stringa a double
        series->append(i, dato);
        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(QString::number(i, 'f', 2)));
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number(dato, 'f', 2)));
    }

    // Update the chart if necessary
    chart->update();  // Optional: depending on how Qt handles updates
}

/*
#include "widgetumidita.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSplineSeries>
#include <QChart>
#include <QValueAxis>
#include <QChartView>
#include <QTableWidgetItem>
#include <QHeaderView>

View::WidgetUmidita::WidgetUmidita(Model::Sensore* s, QWidget *parent)
    : WidgetGrafico(parent) {

}

void View::WidgetUmidita::simulazione(Model::Sensore* sensore) {

    if (QLayout* oldLayout = layout()) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();  // Rimuove i widget figli
            delete item;  // Rimuove il layout item
        }
        delete oldLayout;
    }

    QTableWidget* tabella;
    tabella = new QTableWidget(0, 2, this);
    tabella->setHorizontalHeaderLabels(QStringList() << "misura" << "umidità relativa (%)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    QSplineSeries *series = new QSplineSeries();
    series->setName("spline");

    for (int i = 0; i < 24; ++i) {
        sensore->simulaMisura();  //simula una misura
        std::map<std::string, std::string> info = sensore->getInfo();  //ottiene le informazioni dal sensore
        double dato = std::stod(info["Dato"]);  //conversione "Dato" da stringa a double
        series->append(i, dato);
        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(QString::number(i, 'f', 2)));
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number(dato, 'f', 2)));
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Andamento umidità giornaliera");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 100);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(chartView);
    layout->addWidget(tabella);
    setLayout(layout);
}
*/
