#ifndef SENSORLISTWIDGET_H
#define SENSORLISTWIDGET_H

#include <QWidget>
#include <vector>
#include "../Model/Sensore.h"

class Sensore; // Dichiarazione forward della classe Sensore

class SensorListWidget : public QWidget {
    Q_OBJECT
public:
    SensorListWidget(const std::vector<Model::Sensore*>& sensori, QWidget* parent = nullptr);
};

#endif // SENSORLISTWIDGET_H
