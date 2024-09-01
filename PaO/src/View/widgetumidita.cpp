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
    tabella->setHorizontalHeaderLabels(QStringList() << "Misura" << "Umidità relativa (%)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    chart->legend()->hide();
    series->setName("spline");
    chart->addSeries(series);
    chart->setTitle("Andamento umidità giornaliera");

    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Ora");
    axisX->setRange(0, 24);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Umidità (%)");
    axisY->setRange(0, 100);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chartView->setRenderHint(QPainter::Antialiasing);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(chartView);
    splitter->addWidget(tabella);

    splitter->setSizes(QList<int>() << 2 * 100 << 100);  // 2/3 for chart, 1/3 for table

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);
}

void View::WidgetUmidita::simulazione(Model::Sensore* sensore) {
    series->clear();
    tabella->setRowCount(0);

    for (int i = 0; i < 25; ++i) {
        sensore->simulaMisura();  //simula una misura
        std::map<std::string, std::string> info = sensore->getInfo();
        double dato = std::stod(info["Dato"]);
        series->append(i, dato);
        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(QString::number(i, 'f', 2)));
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number(dato, 'f', 2)));
    }

    chart->update();
}
