#ifndef SENSORLISTWIDGET_H
#define SENSORLISTWIDGET_H

#include <QWidget>
#include <vector>
#include "../Model/sensore.h"
#include "sensorinfowidget.h"

class Sensore; // Dichiarazione forward della classe Sensore

class SensorListWidget : public QWidget {
    Q_OBJECT
public:
    SensorListWidget(std::vector<Model::Sensore*>& sensori, QWidget* parent = nullptr);

signals:
    void sensorClicked(Model::Sensore* sensore); // Segnale emesso quando un sensore viene cliccato
    void sensorCloned();  // Segnale da emettere quando un sensore viene clonato
    void reloadRequested();
    void saveRequested();

private:
    //void createSensorButtons(const std::vector<Model::Sensore*>& sensori);
};

#endif // SENSORLISTWIDGET_H
