#include "widgetvento.h"
#include "../Model/vento.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QtMath>
#include <QPainter>

View::WidgetVento::WidgetVento(Model::Sensore* s, QWidget* parent)
    : WidgetGrafico(parent), vento(static_cast<Model::Vento*>(s)), iterazioniRimanenti(0), angoloCorrente(0) {

    // Creazione del grafico polare
    polarChart = new QPolarChart();

    // Configurazione degli assi
    angularAxis = new QValueAxis();
    angularAxis->setTickCount(9);  // Ogni 45 gradi (0°, 45°, 90°, ...)
    angularAxis->setLabelFormat("%d");
    angularAxis->setRange(0, 360);
    polarChart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    radialAxis = new QValueAxis();
    radialAxis->setLabelFormat("%.1f m/s");
    radialAxis->setRange(0, vento->getMaxVelocita());
    polarChart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);

    // Impostazione del ChartView
    chartView = new QChartView(polarChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    polarChart->setMargins(QMargins(0, 0, 0, 0));
    polarChart->legend()->hide();
    polarChart->setTitle("");

    // Creazione della tabella per visualizzare i dati
    tabella = new QTableWidget(0, 2, this);
    tabella->setHorizontalHeaderLabels(QStringList() << "Velocità (m/s)" << "Angolo (°)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    // Layout principale per contenere il grafico e la tabella
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(chartView, 3);  // 3/4 of the space for the polar chart
    mainLayout->addWidget(tabella, 1);    // 1/4 of the space for the table
    setLayout(mainLayout);

    // Impostazione del timer per l'aggiornamento dell'animazione
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WidgetVento::aggiornaGrafico);
}

void View::WidgetVento::simulazione(Model::Sensore* s) {
    if (vento == s) {
        iterazioniRimanenti = 10;  // Imposta il numero di iterazioni
        polarChart->removeAllSeries();  // Clear any existing series
        tabella->clearContents();
        tabella->setRowCount(0);
        timer->start(1000);  // Avvia il timer per aggiornare il grafico ogni secondo
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

        // Disegna una freccia dal centro al punto
        QPainter painter(chartView->viewport());
        painter.setRenderHint(QPainter::Antialiasing);

        // Calcola la posizione del centro del grafico
        QPointF center(chartView->width() / 2, chartView->height() / 2);

        // Calcola la posizione del punto finale
        double radius = (windData.first / vento->getMaxVelocita()) * (chartView->height() / 2.0);
        double radians = qDegreesToRadians(windData.second);
        QPointF endPoint(center.x() + radius * qCos(radians), center.y() - radius * qSin(radians));

        // Disegna la linea
        QPen pen(Qt::red, 2);
        painter.setPen(pen);
        painter.drawLine(center, endPoint);

        // Disegna la freccia
        static const double arrowSize = 10.0;
        double angle = qAtan2(-(endPoint.y() - center.y()), endPoint.x() - center.x());

        QPointF arrowP1 = endPoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                             cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = endPoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                             cos(angle + M_PI - M_PI / 3) * arrowSize);

        QPolygonF arrowHead;
        arrowHead << endPoint << arrowP1 << arrowP2;

        painter.drawPolygon(arrowHead);

        iterazioniRimanenti--;
    }

    if (iterazioniRimanenti == 0) {
        timer->stop();  // Ferma il timer dopo 10 aggiornamenti
    }
}
