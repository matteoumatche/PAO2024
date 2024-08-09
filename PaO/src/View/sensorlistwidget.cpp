#include "sensorlistwidget.h"
#include "sensorinfowidget.h"
#include "../Model/Sensore.h"
#include <QVBoxLayout>
#include <QPushButton>

// Costruttore della classe SensorListWidget
SensorListWidget::SensorListWidget(const std::vector<Model::Sensore*>& sensori, QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout();

    // Creazione di un SensorInfoWidget per ciascun sensore
    for (Model::Sensore* sensore : sensori) {
        std::map<std::string, std::string> info = sensore->getInfo();
        SensorInfoWidget* sensorWidget = new SensorInfoWidget(info, this);
        layout->addWidget(sensorWidget);

        // Creare un pulsante per rappresentare il sensore
        QPushButton* openButton = new QPushButton("Apri", this);

        // Aggiungi il pulsante al layout
        layout->addWidget(openButton);

        // Collegare il clic del pulsante al segnale di aggiornamento delle informazioni
        connect(openButton, &QPushButton::clicked, this, [this, sensore]() {
            emit sensorClicked(sensore);
        });

        QPushButton* cloneButton = new QPushButton("Clona", this);

        layout->addWidget(cloneButton);

        // Collegare il clic del pulsante "Rimuovi"
        connect(cloneButton, &QPushButton::clicked, this, [this, sensore]() {
            // Qui puoi gestire la rimozione del sensore
            // Ad esempio, emettere un segnale che gestisce la rimozione
            // emit sensorRemoved(sensore);
        });

        // Creare un pulsante "Dettagli"
        QPushButton* deleteButton = new QPushButton("Elimina", this);
        layout->addWidget(deleteButton);

        // Collegare il clic del pulsante "Dettagli"
        connect(deleteButton, &QPushButton::clicked, this, [this, sensore]() {
            // Gestire l'apertura di una finestra di dettagli per il sensore
            // emit sensorDetailsRequested(sensore);
        });
    }

    setLayout(layout);
}
