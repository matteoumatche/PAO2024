#include "widgettempercepita.h"
#include <QVBoxLayout>
#include <QLabel>

View::WidgetTempercepita::WidgetTempercepita(Model::Sensore* s,QWidget *parent)
    : WidgetGrafico(s,parent) {

}

void View::WidgetTempercepita::updateData(/* data specific to temperature sensor */) {
    // Implementazione generica per evitare errori di compilazione
    // Qui puoi aggiornare il widget con nuovi dati, se necessario.
}
