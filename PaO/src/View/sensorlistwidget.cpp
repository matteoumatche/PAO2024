#include "SensorListWidget.h"
#include "SensorInfoWidget.h"
#include "../Model/Sensore.h"
#include <QVBoxLayout>

// Costruttore della classe SensorListWidget
SensorListWidget::SensorListWidget(const std::vector<Model::Sensore*>& sensori, QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout();

    // Creazione di un SensorInfoWidget per ciascun sensore
    for (Model::Sensore* sensore : sensori) {
        std::map<std::string, std::string> info = sensore->getInfo();
        SensorInfoWidget* sensorWidget = new SensorInfoWidget(info, this);
        layout->addWidget(sensorWidget);

    }

    setLayout(layout);
}
