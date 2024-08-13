#include "sensorinfowidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>
#include <QString>
#include <QPushButton>
#include <QTimer>

// Costruttore della classe SensorInfoWidget
SensorInfoWidget::SensorInfoWidget(const std::map<std::string, std::string>& info, QWidget* parent)
    : QWidget(parent) {
    QHBoxLayout* layoutEsterno = new QHBoxLayout(this);
    QVBoxLayout* layoutDati = new QVBoxLayout(this);
    QVBoxLayout* layoutPulsanti = new QVBoxLayout(this);

    // Visualizzazione di ciascuna coppia chiave-valore
    for (const auto& pair : info) {
        QLabel* label = new QLabel(QString::fromStdString(pair.first) + ": " + QString::fromStdString(pair.second), this);
        layoutDati->addWidget(label);
    }
    /*
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
*/
    setLayout(layoutEsterno);
    layoutEsterno->addLayout(layoutDati);
    layoutEsterno->addLayout(layoutPulsanti);
}

// Gestione dell'evento di pressione del mouse
void SensorInfoWidget::mousePressEvent(QMouseEvent* event) {
    emit widgetClicked(); // Emissione del segnale quando il widget viene cliccato
    qDebug() << "Widget cliccato!"; // Aggiungi questa riga per il debug

    // Cambia il colore di sfondo utilizzando QPalette
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::lightGray); // Colore al clic
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    // Ripristina il colore di sfondo dopo un breve intervallo
    QTimer::singleShot(200, this, [this]() {
        QPalette palette = this->palette();
        palette.setColor(QPalette::Window, QColor(255, 255, 255, 0)); // Colore originale
        this->setPalette(palette);
    });

    QWidget::mousePressEvent(event); // Chiamata al gestore dell'evento padre
}
