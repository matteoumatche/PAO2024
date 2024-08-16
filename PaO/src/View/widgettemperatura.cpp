#include "widgettemperatura.h"
#include <QVBoxLayout>
#include <QLabel>

WidgetTemperatura::WidgetTemperatura(Model::Temperatura* sensore, QWidget *parent)
    : QWidget(parent), tempLabel(new QLabel(this)) {

    // Inizializza il layout
    QVBoxLayout* layout = new QVBoxLayout(this);

    tempLabel->setText("Temperatura: " + QString::number(sensore->getDato()) + " °C");
    layout->addWidget(tempLabel);

    setLayout(layout);
}

void WidgetTemperatura::updateData(Model::Temperatura* sensore) {
    // Aggiorna l'interfaccia con i dati forniti dal sensore
    tempLabel->setText("Temperatura: " + QString::number(sensore->getDato()) + " °C");
}
