#include "sensorlistwidget.h"
#include "sensorinfowidget.h"
#include "../Model/sensore.h"
#include <QVBoxLayout>
#include <QLabel>
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

        // PULSANTE "CLONA"--------------------
        QPushButton* cloneButton = new QPushButton("Clona", this);
        layout->addWidget(cloneButton);

        connect(cloneButton, &QPushButton::clicked, this, [this, sensore, layout]() {
            // Clona il sensore usando il metodo clone
            Model::Sensore* clonedSensor = sensore->clone(); // Crea una copia del sensore

            // Aggiungi il nuovo SensorInfoWidget alla lista
            std::map<std::string, std::string> clonedInfo = clonedSensor->getInfo();
            SensorInfoWidget* clonedSensorWidget = new SensorInfoWidget(clonedInfo, this);
            layout->addWidget(clonedSensorWidget);

            // Collega il segnale widgetClicked del nuovo widget
            connect(clonedSensorWidget, &SensorInfoWidget::widgetClicked, this, [this, clonedSensor]() {
                emit sensorClicked(clonedSensor); // Emetti il segnale quando il widget viene cliccato
            });
        });
        //--------------------------------------

        // PULSANTE "ELIMINA"-------------------
        QPushButton* deleteButton = new QPushButton("Elimina", this);
        layout->addWidget(deleteButton);

        connect(deleteButton, &QPushButton::clicked, this, [this, sensore]() {
            // Gestire l'eliminazione del sensore
        });
        //---------------------------------------

        // Collega il segnale widgetClicked al gestore desiderato
        connect(sensorWidget, &SensorInfoWidget::widgetClicked, this, [this, sensore]() {
            emit sensorClicked(sensore); // Emetti il segnale quando il widget viene cliccato
        });
    }

    setLayout(layout);
}
