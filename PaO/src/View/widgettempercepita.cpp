#include "widgettempercepita.h"
#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>

View::WidgetTempercepita::WidgetTempercepita(Model::Sensore* s, QWidget *parent)
    : WidgetGrafico(parent) {

}

void View::WidgetTempercepita::simulazione(Model::Sensore* sensore) {
    qDebug() << "simulazione chiamato per WidgetTemperatura.";
    delete layout();

    QBarSet *setTP = new QBarSet("Temperatura percepita");
    QBarSet *setTR = new QBarSet("Temperatura registrata");

    QBarSeries *series = new QBarSeries();
    QStringList categories;
    categories << "9-10" << "10-11" << "11-12" << "12-13" << "13-14" << "14-15" << "15-16" << "16-17" << "17-18" << "18-19";
    // Create the table widget
    QTableWidget* tabella = new QTableWidget(0, 2, this);
    tabella->setHorizontalHeaderLabels(QStringList() << "Orario" << "Temperatura Percepita (°C)"<<"Temperatura rilevata(°CS)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);
    for (int i = 0; i < 10; ++i) {
        sensore->simulaMisura();  //simula una misura
        std::map<std::string, std::string> info = sensore->getInfo();  //ottiene le informazioni dal sensore
        double percepita = std::stod(info["IndiceCalore"]);  //conversione "Dato" da stringa a double
        double registrata = std::stod(info["Temperatura"]);
        *setTP << percepita;
        *setTR << registrata;

        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(categories[i]));  // Set the category (time)
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number(percepita, 'f', 2)));  // Set the data value
        tabella->setItem(row, 2, new QTableWidgetItem(QString::number(registrata, 'f', 2)));  // Set the data value
    }

    series->append(setTP);
    series->append(setTR);

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
