#include "sensorlistwidget.h"
#include "sensorinfowidget.h"
#include "../Model/sensore.h"
#include "editsensordialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

// Costruttore della classe SensorListWidget
SensorListWidget::SensorListWidget(std::vector<Model::Sensore*>& sensori, QWidget* parent)
    : QWidget(parent) {

    QVBoxLayout* layout = new QVBoxLayout();

    // Creazione di un SensorInfoWidget per ciascun sensore
    for (Model::Sensore* sensore : sensori) {
        std::map<std::string, std::string> info = sensore->getInfo();
        SensorInfoWidget* sensorWidget = new SensorInfoWidget(info, this);
        layout->addWidget(sensorWidget);

        // PULSANTE GENERALE SENSORE-------------
        connect(sensorWidget, &SensorInfoWidget::widgetClicked, this, [this, sensore]() {
            emit sensorClicked(sensore); // Emetti il segnale quando il widget viene cliccato
        });
        //---------------------------------------

        // PULSANTE "CLONA"--------------------
        QPushButton* cloneButton = new QPushButton("Clona", this);
        layout->addWidget(cloneButton);

        connect(cloneButton, &QPushButton::clicked, this, [this, sensore, &sensori]() {
            // Clona il sensore usando il metodo clone
            Model::Sensore* clonedSensor = sensore->clone(); // Crea una copia del sensore

            // Aggiungi il nuovo SensorInfoWidget alla lista
            sensori.push_back(clonedSensor);

            emit sensorCloned();
            qDebug() << "sensore clonato";
        });
        //--------------------------------------

        //PULSANTE "MODIFICA"-------------------
        QPushButton* editButton = new QPushButton("Modifica", this);
        layout->addWidget(editButton);

        connect(editButton, &QPushButton::clicked, this, [this, sensore]() {
            EditSensorDialog* dialog = new EditSensorDialog(sensore, this);
            if (dialog->exec() == QDialog::Accepted) {
                // Aggiorna la visualizzazione del sensore se necessario
                emit sensorUpdated();
                qDebug() << "sensore modificato";
            }
            delete dialog;
        });
        //--------------------------------------

        // PULSANTE "ELIMINA"-------------------
        QPushButton* deleteButton = new QPushButton("Elimina", this);
        layout->addWidget(deleteButton);

        connect(deleteButton, &QPushButton::clicked, this, [this, sensore]() {
            // Gestire l'eliminazione del sensore
        });
        //---------------------------------------

    }

    setLayout(layout);
}
