#include "widgetvento.h"
#include "../Model/vento.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QtMath>
#include <QScatterSeries>
#include <QSplitter>

View::WidgetVento::WidgetVento(Model::Sensore* s, QWidget* parent)
    : WidgetGrafico(parent), vento(static_cast<Model::Vento*>(s)), iterazioniRimanenti(0), angoloCorrente(0) {

    polarChart = new QPolarChart();

    //configurazione assi
    angularAxis = new QValueAxis();
    angularAxis->setTickCount(9);  // Ogni 45 gradi (0°, 45°, 90°, ...)
    angularAxis->setLabelFormat("%d");
    angularAxis->setRange(0, 360);
    polarChart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    radialAxis = new QValueAxis();
    radialAxis->setLabelFormat("%.1f m/s");
    radialAxis->setRange(0, vento->getMaxVelocita());
    polarChart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);

    //impostazioni ChartView
    chartView = new QChartView(polarChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    polarChart->setMargins(QMargins(0, 0, 0, 0));
    polarChart->legend()->hide();
    polarChart->setTitle("Tracciamento direzione rispetto a offset (°) e velocità (m/s) vento");

    // Creazione della tabella per visualizzare i dati
    tabella = new QTableWidget(0, 3, this);
    tabella->setHorizontalHeaderLabels(QStringList() << "Velocità (m/s)" << "Angolo (°)" << "Ora (hh:mm:ss)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(chartView);
    splitter->addWidget(tabella);

    splitter->setSizes(QList<int>() << 2 * 100 << 100);  // 2/3 per il grafico, 1/3 per la tabella

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    //mainLayout->addWidget(chartView, 3);  // 3/4 of the space for the polar chart
    //mainLayout->addWidget(tabella, 1);    // 1/4 of the space for the table

    mainLayout->addWidget(splitter);
    setLayout(mainLayout);

    //timer per l'aggiornamento dell'animazione
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WidgetVento::aggiornaGrafico);
}

void View::WidgetVento::simulazione(Model::Sensore* s) {
    if (vento == s) {
        iterazioniRimanenti = 10;  //numero di iterazioni
        polarChart->removeAllSeries();
        tabella->clearContents();
        tabella->setRowCount(0);
        timer->start(1000);  //timer per aggiornare il grafico ogni secondo
    }
}

void View::WidgetVento::aggiornaGrafico() {
    if (iterazioniRimanenti > 0) {
        vento->simulaMisura();
        auto windData = vento->getDato();

        // Aggiungi i nuovi dati alla tabella
        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(QString::number(windData.first, 'f', 2)));
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number(windData.second, 'f', 2)));
        tabella->setItem(row, 2, new QTableWidgetItem(QDateTime::currentDateTime().toString("HH:mm:ss")));

        QScatterSeries* scatterSeries = new QScatterSeries();
        scatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        scatterSeries->setMarkerSize(10.0);
        scatterSeries->append(windData.second, windData.first);
        polarChart->addSeries(scatterSeries);
        scatterSeries->attachAxis(angularAxis);
        scatterSeries->attachAxis(radialAxis);

        QLineSeries* arrowSeries = new QLineSeries();
        arrowSeries->append(0, 0);
        arrowSeries->append(windData.second, windData.first);
        polarChart->addSeries(arrowSeries);
        arrowSeries->attachAxis(angularAxis);
        arrowSeries->attachAxis(radialAxis);

        iterazioniRimanenti--;
    }

    if (iterazioniRimanenti == 0) {
        timer->stop();  // Ferma il timer dopo 10 aggiornamenti
    }
}

