#include "sensorlistwidget.h"
#include "sensorinfowidget.h"
#include "../Model/Sensore.h"
#include <QVBoxLayout>
#include <QLabel>

// Costruttore della classe SensorListWidget
SensorListWidget::SensorListWidget(const std::vector<Model::Sensore*>& sensori, QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout();

    // Creazione di un SensorInfoWidget per ciascun sensore
    for (Model::Sensore* sensore : sensori) {
        std::map<std::string, std::string> info = sensore->getInfo();
        SensorInfoWidget* sensorWidget = new SensorInfoWidget(info, this);
        layout->addWidget(sensorWidget);

        // Collega il segnale widgetClicked al gestore desiderato
        connect(sensorWidget, &SensorInfoWidget::widgetClicked, this, [this, sensore]() {
            emit sensorClicked(sensore); // Emetti il segnale quando il widget viene cliccato
        });
    }

    setLayout(layout);
}
