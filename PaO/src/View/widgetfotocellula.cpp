#include "widgetfotocellula.h"
#include <QVBoxLayout>
#include <QLabel>

View::WidgetFotocellula::WidgetFotocellula(Model::Sensore* s,QWidget *parent)
    : WidgetGrafico(parent) {
    // Layout di base per il widget
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Aggiungi un'etichetta generica come contenuto del widget
    QLabel* label = new QLabel("Dati del sensore Fotocellula", this);
    layout->addWidget(label);

    // Imposta il layout al widget
    setLayout(layout);
}

void View::WidgetFotocellula::updateData(/* data specific to wind sensor */) {
    // Implementazione generica per evitare errori di compilazione
    // Qui puoi aggiornare il widget con nuovi dati, se necessario.
}
