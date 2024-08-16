#include "widgettemperatura.h"
#include <QVBoxLayout>
#include <QLabel>

WidgetTemperatura::WidgetTemperatura(Model::Temperatura* sensore, QWidget *parent)
    : QWidget(parent), tempLabel(new QLabel(this)) {

    qDebug() << "WidgetTemperatura creato";


    // Inizializza il layout
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Aggiungi un'etichetta per mostrare un messaggio
    QLabel* label = new QLabel("Dati del sensore Temperatura", this);
    layout->addWidget(label);

    setLayout(layout);

    qDebug() << "WidgetTemperatura creato e visualizzato.";

}

void WidgetTemperatura::updateData(Model::Temperatura* sensore) {
    // Aggiorna l'interfaccia con i dati forniti dal sensore
    tempLabel->setText("Temperatura: " + QString::number(sensore->getDato()) + " °C");

    qDebug() << "updateData chiamato per WidgetTemperatura.";

}
