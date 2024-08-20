#include "widgetvento.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <cmath>


View::WidgetVento::WidgetVento(Model::Sensore* s, QWidget* parent)
    : WidgetGrafico(s,parent), vento(static_cast<Model::Vento*>(s)) {
}


void View::WidgetVento::simulazione() {
   // datiSimulati.clear();
   // for (int i = 0; i < 10; ++i) {
        vento->simulaMisura();
       // datiSimulati.push_back(vento->getDato());
    //}
   // mostraGrafico = true;
    update();  // Trigger per il repaint
}
/*
void View::WidgetVento::misura(double valoreReale) {
    vento->Misura(std::make_pair(valoreReale, 0)); // Simula una misura reale
    mostraGrafico = false;
    update();  // Trigger per il repaint
}*/
/*
void View::WidgetVento::valoreMisura() {

    misura(10);
}*/

void View::WidgetVento::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    /*if (mostraGrafico) {
        // Modalità grafico
        int larghezza = this->width();
        int altezza = this->height();
        int margine = 20;
        int areaGraficoLarghezza = larghezza - 2 * margine;
        int areaGraficoAltezza = altezza - 2 * margine;

        // Disegna gli assi
        painter.setPen(Qt::black);
        painter.drawLine(margine, altezza - margine, larghezza - margine, altezza - margine); // Asse X
        painter.drawLine(margine, altezza - margine, margine, margine); // Asse Y

        // Determina i range dei valori
        double maxVelocita = vento->getMaxVelocita();
        double maxAngolo = 360.0;

        // Disegna i punti simulati
        QPen penna(Qt::red, 2);
        painter.setPen(penna);
        for (const auto& dato : datiSimulati) {
            double x = margine + dato.second / maxAngolo * areaGraficoLarghezza;
            double y = altezza - margine - dato.first / maxVelocita * areaGraficoAltezza;
            painter.drawPoint(static_cast<int>(x), static_cast<int>(y));
        }

    } else {*/
        // Modalità bussola
        auto windData = vento->getDato();
        double velocita = windData.first;
        double angolo = windData.second;

        int larghezza = this->width();
        int altezza = this->height();
        QPoint centro(larghezza / 2, altezza / 2);

        int raggio = std::min(larghezza, altezza) / 2 - 10;
        painter.setPen(Qt::black);
        painter.drawEllipse(centro, raggio, raggio);

        double angoloRad = qDegreesToRadians(angolo);
        QPoint puntoFinale(centro.x() + raggio * std::cos(angoloRad) * (velocita / vento->getMaxVelocita()),
                           centro.y() - raggio * std::sin(angoloRad) * (velocita / vento->getMaxVelocita()));

        QPen penna(Qt::red, 2);
        painter.setPen(penna);
        painter.drawLine(centro, puntoFinale);
    //}
}

