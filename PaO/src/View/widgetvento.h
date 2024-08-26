#ifndef WIDGETVENTO_H
#define WIDGETVENTO_H

#include "widgetgrafico.h"
#include "../Model/vento.h"
#include <QTimer>
#include <QTableWidget>

namespace View {

class WidgetVento : public WidgetGrafico {
    Q_OBJECT

public:
    explicit WidgetVento(Model::Sensore* s, QWidget* parent = nullptr);

public slots:
    void simulazione(Model::Sensore* s) override;  // Slot per iniziare la simulazione

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void aggiornaBussola();  // Slot per aggiornare la bussola e animare la freccia

private:
    Model::Vento* vento;            // Puntatore al sensore del vento
    QTimer* timer;                  // Timer per gestire l'animazione della bussola
    QTableWidget* tabella;          // Tabella per visualizzare i dati di velocità e angolo
    double angoloCorrente;          // Memorizza l'angolo corrente della freccia
    int iterazioniRimanenti;        // Contatore per fermare l'aggiornamento dopo 10 iterazioni
};

}  // namespace View

#endif // WIDGETVENTO_H

