#include "sensorlistwidget.h"
#include "sensorinfowidget.h"
#include "../Model/sensore.h"
#include "editsensordialog.h"
//#include "../mainwindow.h"
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

        connect(sensorWidget, &SensorInfoWidget::sensorSelected,this,View::SensorListWidget::onSensorSelected);

        // PULSANTE "CLONA"--------------------
        QPushButton* cloneButton = new QPushButton("Clona", this);
        layoutBottoni->addWidget(cloneButton);

        connect(cloneButton, &QPushButton::clicked, cloneButton, [this,&sensori,sensore]{
            sensori.push_back(sensore->clone());
            emit updateList();
        });
        //--------------------------------------

        /*PULSANTE "MODIFICA"-------------------
        QPushButton* editButton = new QPushButton("Modifica", this);
        layoutBottoni->addWidget(editButton);
        connect(editButton, &QPushButton::clicked, this, [this, &sensori, sensore]() {
            EditSensorDialog* dialog = new EditSensorDialog(sensore,sensori, this);
            qDebug() << "creato edit dialog";
            if (dialog->exec() == QDialog::Accepted) {
                // Aggiorna la visualizzazione del sensore se necessario
                emit updateList();
                qDebug() << "sensore modificato";
            }
        });
        //--------------------------------------*/

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
            emit updateList();
            qDebug() << "sensore eliminato";
        });
        //---------------------------------------

        layoutInterno->addLayout(layoutBottoni);
        layout->addLayout(layoutInterno);
    }

    setLayout(layout);
}


void View::SensorListWidget::onSensorSelected(Model::Sensore* s){
    qDebug() << "View::SensorListWidget::onSensorSelected";
    emit sensorSelected(s);
}
