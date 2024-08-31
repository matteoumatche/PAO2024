#include "widgettemperatura.h"
#include <QVBoxLayout>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSplitter>

View::WidgetTemperatura::WidgetTemperatura(Model::Sensore* sensore, QWidget *parent)
    : WidgetGrafico(parent),
      set(new QBarSet("Temperatura")),
      series(new QBarSeries()),
      chart(new QChart()),
      chartView(new QChartView(chart)),
      tabella(new QTableWidget(0, 2, this))
{
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Andamento della Temperatura");

    QStringList categories;
    categories << "9-10" << "10-11" << "11-12" << "12-13" << "13-14" << "14-15" << "15-16" << "16-17" << "17-18" << "18-19";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("ore");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(-10, 40);
    axisY->setTitleText("Temperatura (°C)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    tabella->setHorizontalHeaderLabels(QStringList() << "Orario" << "Temperatura (°C)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(chartView);
    splitter->addWidget(tabella);

    splitter->setSizes(QList<int>() << 2 * 100 << 100);  // 2/3 per il grafico, 1/3 per la tabella

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);
}

void View::WidgetTemperatura::simulazione(Model::Sensore* sensore) {
    set->remove(0, set->count());
    tabella->setRowCount(0);

    QStringList categories;
    categories << "9-10" << "10-11" << "11-12" << "12-13" << "13-14" << "14-15" << "15-16" << "16-17" << "17-18" << "18-19";

    for (int i = 0; i < 10; ++i) {
        sensore->simulaMisura();
        std::map<std::string, std::string> info = sensore->getInfo();
        double dato = std::stod(info["Dato"]);
        *set << dato;

        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(categories[i]));
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number(dato, 'f', 2)));
    }

    chart->update();
}
