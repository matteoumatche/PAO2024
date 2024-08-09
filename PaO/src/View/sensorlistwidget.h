#ifndef SENSORLISTWIDGET_H
#define SENSORLISTWIDGET_H

#include <QWidget>
#include <vector>
#include "../Model/Sensore.h"
#include "sensorinfowidget.h"

class Sensore; // Dichiarazione forward della classe Sensore

class SensorListWidget : public QWidget {
    Q_OBJECT
public:
    SensorListWidget(const std::vector<Model::Sensore*>& sensori, QWidget* parent = nullptr);

signals:
    void sensorClicked(const Model::Sensore* sensore); // Segnale emesso quando un sensore viene cliccato

private:
    void createSensorButtons(const std::vector<Model::Sensore*>& sensori);
};

#endif // SENSORLISTWIDGET_H
