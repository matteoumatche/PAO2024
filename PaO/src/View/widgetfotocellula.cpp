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

}

void View::WidgetFotocellula::simulazione(Model::Sensore* s) {

    delete layout();

    qDebug()<<"sim foto 4";
    QSplineSeries *series = new QSplineSeries();
    series->setName("visitatori");

    // Creazione della tabella per visualizzare i dati

    QTableWidget* tabella;
    tabella = new QTableWidget(0, 2, this);
    tabella->setHorizontalHeaderLabels(QStringList() << "numero di ospiti" <<"ora(hh:mm:ss)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    std::tm ora;
    ora.tm_hour = 10; // Imposta l'ora di apertura alle 10:00
    ora.tm_min = 0;
    ora.tm_sec = 0;
    int j = 0;

    for (int i = 0; i < 50; i++) {

        qDebug() << "sim foto i:" << i;

        for (std::vector<Model::Sensore*>::iterator it = sensori->begin(); it != sensori->end(); it++) {
            if ((*it)->getInfo()["Tipo"] == "Fotocellula") {
                qDebug() << "sim foto j:" << j;
                bool attivo = dynamic_cast<Model::Fotocellula*>(*it)->Misura(&ora);  // Simula una misura per l'ora corrente
                qDebug() << "sim foto simula j:" << j;
                attivo ? j++ :j;
            }
        }
        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(QString::number(j, 'f', 2)));
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number((ora.tm_hour + ora.tm_min / 60.0), 'f', 2)));

        qDebug() << "series";
        // Aggiungi i valori ottenuti alla serie per la visualizzazione grafica
        series->append(ora.tm_hour + ora.tm_min / 60.0, j); // 'i' rappresenta l'indice di iterazione, 'j' il valore di attivo/non attivo
        // Incrementa l'ora di 10 minuti per ogni iterazione
        ora.tm_min += 10;

        // Normalizza l'oggetto std::tm nel caso si superino i 60 minuti
        std::mktime(&ora);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("andamento numero visitatori");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, j+(0.2*j));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(chartView);
    splitter->addWidget(tabella);

    splitter->setSizes(QList<int>() << 2 * 100 << 100);  // 2/3 per il grafico, 1/3 per la tabella

    // Layout principale per contenere il grafico e la tabella
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    //mainLayout->addWidget(chartView, 3);  // 3/4 of the space for the polar chart
    //mainLayout->addWidget(tabella, 1);    // 1/4 of the space for the table

    mainLayout->addWidget(splitter);
    setLayout(mainLayout);
    /*
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(chartView);
    layout->addWidget(tabella);
    setLayout(layout);*/
}
