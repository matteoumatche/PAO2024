#include "sensorlistwidget.h"
#include "sensorinfowidget.h"
#include "../Model/sensore.h"
#include "editsensordialog.h"
#include "../mainwindow.h"
#include <vector>
#include <QVBoxLayout>
#include<QString>
#include <QLabel>
#include <QPushButton>
#include <QLayout>


// Costruttore della classe SensorListWidget
View::SensorListWidget::SensorListWidget(std::vector<Model::Sensore*>& sensori, QWidget* parent)
    : QWidget(parent) {

    QVBoxLayout* layout = new QVBoxLayout();


    // Creazione di un SensorInfoWidget per ciascun sensore
    for (Model::Sensore* sensore : sensori) {
        std::map<std::string, std::string> info = sensore->getInfo();
        SensorInfoWidget* sensorWidget = new SensorInfoWidget(info, this);
        QHBoxLayout* layoutInterno = new QHBoxLayout();
        QVBoxLayout* layoutBottoni = new QVBoxLayout();
        layoutInterno->addWidget(sensorWidget);

        // PULSANTE GENERALE SENSORE-------------
        connect(sensorWidget, &SensorInfoWidget::widgetClicked, this, [this, sensore]() {
            emit sensorClicked(sensore); // Emetti il segnale quando il widget viene cliccato
        });
        //---------------------------------------

        // PULSANTE "CLONA"--------------------
        QPushButton* cloneButton = new QPushButton("Clona", this);
        layoutBottoni->addWidget(cloneButton);

        connect(cloneButton, &QPushButton::clicked, cloneButton, [this,&sensori,sensore]{
            sensori.push_back(sensore->clone());
            this->sendRequestUpdateList();

        });
        //--------------------------------------

        //PULSANTE "MODIFICA"-------------------
        QPushButton* editButton = new QPushButton("Modifica", this);
        layoutBottoni->addWidget(editButton);
        connect(editButton, &QPushButton::clicked, this, [this, sensore]() {
            EditSensorDialog* dialog = new EditSensorDialog(sensore, this);
            if (dialog->exec() == QDialog::Accepted) {
                // Aggiorna la visualizzazione del sensore se necessario
                View::SensorListWidget::sendRequestUpdateList();
                qDebug() << "sensore modificato";
            }
            delete dialog;
        });
        //--------------------------------------

        // PULSANTE "ELIMINA"-------------------
        QPushButton* deleteButton = new QPushButton("Elimina", this);
        layoutBottoni->addWidget(deleteButton);
        connect(deleteButton, &QPushButton::clicked, this, [ &sensori, sensore, this]() {
            // Iteriamo su ogni elemento del vettore sensori utilizzando un iteratore
            for (auto it = sensori.begin(); it != sensori.end(); ++it) {
                // Se l'ID dell'elemento corrente corrisponde all'ID del sensore da rimuovere
                if ((*it)->getID() == sensore->getID()) {
                    // Rimuoviamo l'elemento dal vettore
                    sensori.erase(it);
                    // Uscire dal ciclo dopo aver rimosso l'elemento, poiché non è necessario continuare
                    break;
                }
            }
            this->sendRequestUpdateList();
            qDebug() << "sensore eliminato";
        });
        //---------------------------------------

        layoutInterno->addLayout(layoutBottoni);
        layout->addLayout(layoutInterno);
    }

    setLayout(layout);
}

void View::SensorListWidget::sendRequestUpdateList(){
    qDebug() << "richiesta inviata";
    emit View::SensorListWidget::updateList();
}

/*
void View::SensorListWidget::updateSensors(std::vector<Model::Sensore*>& sensori) {
    // Rimuovi tutti i widget figli esistenti
    QLayoutItem* item;
    while ((item = layout()->takeAt(0)) != nullptr) {
        delete item->widget(); // elimina il widget
        delete item; // elimina l'item del layout
    }

    // Ricrea i widget basati sui sensori aggiornati
    for (Model::Sensore* sensore : sensori) {
        std::map<std::string, std::string> info = sensore->getInfo();
        SensorInfoWidget* sensorWidget = new SensorInfoWidget(info, this);
        QHBoxLayout* layoutInterno = new QHBoxLayout();
        QVBoxLayout* layoutBottoni = new QVBoxLayout();
        layoutInterno->addWidget(sensorWidget);

        // PULSANTE GENERALE SENSORE
        connect(sensorWidget, &SensorInfoWidget::widgetClicked, this, [this, sensore]() {
            emit sensorClicked(sensore);
        });

        // PULSANTE "CLONA"
        QPushButton* cloneButton = new QPushButton("Clona", this);
        layoutBottoni->addWidget(cloneButton);

        connect(cloneButton, &QPushButton::clicked, this, [this, &sensori, sensore] {
            sensori.push_back(sensore->clone());
            this->sendRequestUpdateList();
        });

        // PULSANTE "MODIFICA"
        QPushButton* editButton = new QPushButton("Modifica", this);
        layoutBottoni->addWidget(editButton);
        connect(editButton, &QPushButton::clicked, this, [this, sensore]() {
            EditSensorDialog* dialog = new EditSensorDialog(sensore, this);
            if (dialog->exec() == QDialog::Accepted) {
                sendRequestUpdateList();
                qDebug() << "sensore modificato";
            }
            delete dialog;
        });

        // PULSANTE "ELIMINA"
        QPushButton* deleteButton = new QPushButton("Elimina", this);
        layoutBottoni->addWidget(deleteButton);
        connect(deleteButton, &QPushButton::clicked, this, [&sensori, sensore, this]() {
            auto it = std::find_if(sensori.begin(), sensori.end(), [sensore](Model::Sensore* s) {
                return s->getID() == sensore->getID();
            });
            if (it != sensori.end()) {
                sensori.erase(it);
                sendRequestUpdateList();
                qDebug() << "sensore eliminato";
            }
        });

        layoutInterno->addLayout(layoutBottoni);
        layout()->addLayout(layoutInterno);
    }
}*/


