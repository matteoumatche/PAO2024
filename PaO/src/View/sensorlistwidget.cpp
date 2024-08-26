#include "sensorlistwidget.h"
#include "sensorinfowidget.h"

#include <QLayout>

View::SensorListWidget::SensorListWidget(std::vector<Model::Sensore*>& sensori, QWidget* parent)
    : QWidget(parent), sensori(sensori) {

    QVBoxLayout* layout = new QVBoxLayout();

    // Creazione di un SensorInfoWidget per ciascun sensore
    for (Model::Sensore* sensore : sensori) {
        std::map<std::string, std::string> info = sensore->getInfo();
        SensorInfoWidget* sensorWidget = new SensorInfoWidget(info, this);

        QHBoxLayout* layoutInterno = new QHBoxLayout();
        layoutInterno->addWidget(sensorWidget);

        QVBoxLayout* layoutBottoni = new QVBoxLayout();

        connect(sensorWidget, &SensorInfoWidget::sensorSelected,this, &SensorListWidget::onSensorSelected);

        layoutInterno->addLayout(layoutBottoni);
        layout->addLayout(layoutInterno);
    }

    setLayout(layout);
}

void View::SensorListWidget::onSensorSelected(const std::string& sensorID){
    qDebug() << "passo 2";
    emit sensorSelected(sensorID);
}

