#include "widgettemperatura.h"
#include <QVBoxLayout>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QTableWidgetItem>
#include <QHeaderView>

View::WidgetTemperatura::WidgetTemperatura(Model::Sensore* sensore, QWidget *parent)
    : WidgetGrafico(parent)
{

}

void View::WidgetTemperatura::simulazione(Model::Sensore* sensore) {
    qDebug() << "simulazione chiamato per WidgetTemperatura.";
    delete layout();

    QBarSet *set = new QBarSet("Prova");

    QStringList categories;
    categories << "9-10" << "10-11" << "11-12" << "12-13" << "13-14" << "14-15" << "15-16" << "16-17" << "17-18" << "18-19";

    // Create the table widget
    QTableWidget* tabella = new QTableWidget(0, 2, this);
    tabella->setHorizontalHeaderLabels(QStringList() << "Orario" << "Temperatura (°C)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    for (int i = 0; i < 10; ++i) {
        sensore->simulaMisura();  //simula una misura
        std::map<std::string, std::string> info = sensore->getInfo();  //ottiene le informazioni dal sensore
        double dato = std::stod(info["Dato"]);  //conversione "Dato" da stringa a double
        *set << dato;

        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(categories[i]));  // Set the category (time)
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number(dato, 'f', 2)));  // Set the data value
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(-10,40);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(chartView);
    layout->addWidget(tabella);

    setLayout(layout);

}
