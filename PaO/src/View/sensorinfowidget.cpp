#include "sensorinfowidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>
#include <QString>

// Costruttore della classe SensorInfoWidget
SensorInfoWidget::SensorInfoWidget(const std::map<std::string, std::string>& info, QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Visualizzazione di ciascuna coppia chiave-valore
    for (const auto& pair : info) {
        QLabel* label = new QLabel(QString::fromStdString(pair.first) + ": " + QString::fromStdString(pair.second), this);
        layout->addWidget(label);
    }

    setLayout(layout);
}

