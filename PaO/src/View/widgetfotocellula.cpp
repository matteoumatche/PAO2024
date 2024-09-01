#include "widgetfotocellula.h"
#include "../Model/fotocellula.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QSplineSeries>
#include <QChart>
#include <QValueAxis>
#include <QChartView>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSplitter>

View::WidgetFotocellula::WidgetFotocellula(std::vector<Model::Sensore*>* s ,QWidget *parent)
    : WidgetGrafico(parent), sensori(s){

    series = new QSplineSeries();
    series->setName("Visitatori");
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Andamento numero visitatori");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 1000);
    chart->axes(Qt::Horizontal).first()->setRange(10, 18);
    chart->axes(Qt::Vertical).first()->setTitleText("N. visitatori");
    chart->axes(Qt::Horizontal).first()->setTitleText("Ore (hh)");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    tabella = new QTableWidget(0, 2, this);
    tabella->setHorizontalHeaderLabels(QStringList() << "N. ospiti" << "Ora (hh:mm:ss)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(chartView);
    splitter->addWidget(tabella);

    splitter->setSizes(QList<int>() << 2 * 100 << 100);  // 2/3 per il grafico, 1/3 per la tabella

    // Layout principale per contenere il grafico e la tabella
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    mainLayout->addWidget(splitter);
    setLayout(mainLayout);

}

void View::WidgetFotocellula::simulazione(Model::Sensore* s) {
    tabella->setRowCount(0);
    chart->removeAllSeries();
    QSplineSeries* serie = new QSplineSeries();

    std::tm ora;
    ora.tm_hour = 10; // Imposta l'ora di apertura alle 10:00
    ora.tm_min = 0;
    ora.tm_sec = 0;
    int j = 0;

    for (int i = 0; i < 50; i++) {

        for (std::vector<Model::Sensore*>::iterator it = sensori->begin(); it != sensori->end(); it++) {
            if ((*it)->getInfo()["Tipo"] == "Fotocellula") {
                bool attivo = dynamic_cast<Model::Fotocellula*>(*it)->Misura(&ora);  // Simula una misura per l'ora corrente
                attivo ? j++ :j;
            }
        }
        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(QString::number(j, 'f', 2)));
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number((ora.tm_hour + ora.tm_min / 60.0), 'f', 2)));

        // Aggiungi i valori ottenuti alla serie per la visualizzazione grafica
        serie->append(ora.tm_hour + ora.tm_min / 60.0, j);
        // Incrementa l'ora di 10 minuti per ogni iterazione
        ora.tm_min += 10;

        // Normalizza l'oggetto std::tm nel caso si superino i 60 minuti
        std::mktime(&ora);
    }


    chart->axes(Qt::Vertical).first()->setRange(0, j+(0.3*j));
    chart->addSeries(serie);
    chart->update();
    //chart->repaint();
    delete layout();
    // Layout principale per contenere il grafico e la tabella
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    mainLayout->addWidget(splitter);
    setLayout(mainLayout);
}
