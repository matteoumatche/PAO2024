#include "widgetvento.h"
#include "../Model/vento.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QPen>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <cmath>

View::WidgetVento::WidgetVento(Model::Sensore* s, QWidget* parent)
    : WidgetGrafico(parent), vento(static_cast<Model::Vento*>(s)), angoloCorrente(0), iterazioniRimanenti(0) {

    // Layout principale per contenere la bussola e la tabella
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // Layout verticale per la bussola
    QVBoxLayout* compassLayout = new QVBoxLayout();
    mainLayout->addLayout(compassLayout);

    // Creazione della tabella per visualizzare i dati
    tabella = new QTableWidget(0, 2, this);
    tabella->setHorizontalHeaderLabels(QStringList() << "Velocità" << "Angolo");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);
    mainLayout->addWidget(tabella);

    setLayout(mainLayout);

    // Impostazione del timer per l'aggiornamento dell'animazione
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WidgetVento::aggiornaBussola);

    // Inizializzare la visualizzazione della bussola
    update();
}

void View::WidgetVento::simulazione(Model::Sensore* s) {
    if (vento == s) {
        iterazioniRimanenti = 10;  // Imposta il numero di iterazioni
        timer->start(1000);  // Avvia il timer per aggiornare la bussola ogni secondo
    }
}

void View::WidgetVento::aggiornaBussola() {
    if (iterazioniRimanenti > 0) {
        vento->simulaMisura();
        auto windData = vento->getDato();

        // Aggiungi i nuovi dati alla tabella
        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(QString::number(windData.first, 'f', 2)));
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number(windData.second, 'f', 2)));

        // Calcola il movimento graduale della freccia
        double nuovoAngolo = windData.second;
        double step = (nuovoAngolo - angoloCorrente) / 20.0;  // Dividi il movimento in 20 step

        angoloCorrente = nuovoAngolo;
        update();

        iterazioniRimanenti--;
    }

    if (iterazioniRimanenti == 0) {
        timer->stop();  // Ferma il timer dopo 10 aggiornamenti
    }
}

void View::WidgetVento::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int larghezza = this->width() / 2;  // Disegna sulla metà sinistra
    int altezza = this->height();
    QPoint centro(larghezza / 2, altezza / 2);

    int raggio = std::min(larghezza, altezza) / 2 - 10;
    painter.setPen(Qt::black);
    painter.drawEllipse(centro, raggio, raggio);

    // Disegna le graduazioni della bussola
    for (int i = 0; i < 360; ++i) {
        double angoloRad = qDegreesToRadians(static_cast<double>(i));
        QPoint tickStart(centro.x() + raggio * std::cos(angoloRad),
                         centro.y() - raggio * std::sin(angoloRad));
        QPoint tickEnd(centro.x() + (raggio - 10) * std::cos(angoloRad),
                       centro.y() - (raggio - 10) * std::sin(angoloRad));
        painter.drawLine(tickStart, tickEnd);
    }

    // Disegna la freccia
    double velocita = vento->getDato().first;
    double angoloRad = qDegreesToRadians(angoloCorrente);
    QPoint puntoFinale(centro.x() + raggio * std::cos(angoloRad) * (velocita / vento->getMaxVelocita()),
                       centro.y() - raggio * std::sin(angoloRad) * (velocita / vento->getMaxVelocita()));

    QPen penna(Qt::red, 2);
    painter.setPen(penna);
    painter.drawLine(centro, puntoFinale);
}

