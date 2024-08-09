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
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Visualizzazione di ciascuna coppia chiave-valore
    for (const auto& pair : info) {
        QLabel* label = new QLabel(QString::fromStdString(pair.first) + ": " + QString::fromStdString(pair.second), this);
        layout->addWidget(label);
    }

    /*
    // PULSANTE "CLONA"--------------------
    QPushButton* cloneButton = new QPushButton("Clona", this);
    layout->addWidget(cloneButton);

    connect(cloneButton, &QPushButton::clicked, this, [this, sensore]() {
        // Qui puoi gestire la clonazione del sensore
        // Ad esempio, emettere un segnale che gestisce la clonazione
        // emit sensorRemoved(sensore);
    });
    //--------------------------------------

    // PULSANTE "ELIMINA"-------------------
    QPushButton* deleteButton = new QPushButton("Elimina", this);
    layout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, [this, sensore]() {
        // Gestire l'eliminazione del sensore
        // emit sensorDetailsRequested(sensore);
    });
    //---------------------------------------
    */

    setLayout(layout);
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
        palette.setColor(QPalette::Window, Qt::white); // Colore originale
        this->setPalette(palette);
    });

    QWidget::mousePressEvent(event); // Chiamata al gestore dell'evento padre
}
