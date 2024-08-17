#include "sensorinfowidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>
#include <QString>
#include <QPushButton>
#include <QTimer>

// Costruttore della classe SensorInfoWidget
View::SensorInfoWidget::SensorInfoWidget(const std::map<std::string, std::string>& info, QWidget* parent)
    : QWidget(parent) {

    QVBoxLayout* layoutDati = new QVBoxLayout(this);

    // Visualizzazione di ciascuna coppia chiave-valore
    for (const auto& pair : info) {
        QLabel* label = new QLabel(QString::fromStdString(pair.first) + ": " + QString::fromStdString(pair.second), this);
        layoutDati->addWidget(label);
    }

    setLayout(layoutDati);

}

void View::SensorInfoWidget::mousePressEvent(QMouseEvent* event) {
    emit sensorSelected(m_sensorInfo); // Emissione del segnale quando il widget viene cliccato
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
