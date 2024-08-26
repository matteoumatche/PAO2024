#ifndef SENSORLISTWIDGET_H
#define SENSORLISTWIDGET_H

#include "../Model/sensore.h"

#include <QWidget>

namespace View{

class SensorListWidget : public QWidget {
    Q_OBJECT

private:
    Model::Sensore* selezionato;
    std::vector<Model::Sensore*>& sensori;

public:
    SensorListWidget(std::vector<Model::Sensore*>& sensori, QWidget* parent = nullptr);

signals:
    void updateList();
    void sensorSelected(const std::string& sensorID);

public slots:
    void onSensorSelected(const std::string& sensorID);
};

}

#endif
