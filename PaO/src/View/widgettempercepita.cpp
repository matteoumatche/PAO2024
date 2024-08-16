#include "widgettempercepita.h"
#include <QVBoxLayout>
#include <QLabel>

WidgetTempercepita::WidgetTempercepita(QWidget *parent)
    : QWidget(parent) {
    // Layout di base per il widget
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Aggiungi un'etichetta generica come contenuto del widget
    QLabel* label = new QLabel("Dati del sensore Temperatura Percepita", this);
    layout->addWidget(label);

    // Imposta il layout al widget
    setLayout(layout);
}

void WidgetTempercepita::updateData(/* data specific to temperature sensor */) {
    // Implementazione generica per evitare errori di compilazione
    // Qui puoi aggiornare il widget con nuovi dati, se necessario.
}
