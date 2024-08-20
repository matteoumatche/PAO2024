#include "sensorinfowidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>
#include <QString>
#include <QPushButton>
#include <QTimer>

// Costruttore della classe SensorInfoWidget
View::SensorInfoWidget::SensorInfoWidget(const std::map<std::string, std::string>& info, QWidget* parent)
    : QWidget(parent), sensorID(""){

    QVBoxLayout* layoutDati = new QVBoxLayout(this);

    QStringList keysToDisplay = {"Tipo", "ID", "Nome"};

    for (const auto& pair : info) {
        QString key = QString::fromStdString(pair.first);
        QString value = QString::fromStdString(pair.second);

        if (key == "ID") {
            sensorID = pair.second; // Memorizza l'ID del sensore
        }

        if (keysToDisplay.contains(key)) {
            QLabel* label = new QLabel(key + ": " + QString::fromStdString(pair.second), this);
            layoutDati->addWidget(label);
        }
    }

    setLayout(layoutDati);

}

void View::SensorInfoWidget::mousePressEvent(QMouseEvent* event) {
    qDebug() << "passo 1";
    emit sensorSelected(sensorID); // Emissione del segnale quando il widget viene cliccato
    QWidget::mousePressEvent(event); // Chiamata al gestore dell'evento padre
}

/* Gestione dell'evento di pressione del mouse
void View::SensorInfoWidget::mousePressEvent(QMouseEvent* event, Model::Sensore* sensore) {
    emit widgetClicked(sensore); // Emissione del segnale quando il widget viene cliccato
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
}*/
