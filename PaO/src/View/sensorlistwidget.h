#ifndef SENSORLISTWIDGET_H
#define SENSORLISTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <vector>
#include "../Model/sensore.h"
#include "sensorinfowidget.h"

namespace View{

class SensorListWidget : public QWidget {
    Q_OBJECT

private:
    Model::Sensore* selezionato;

public:
    SensorListWidget(std::vector<Model::Sensore*>& sensori, QWidget* parent = nullptr);

signals:
    void updateList(); //emesso quando i dati dei sensori cambiano
};
}
#endif // SENSORLISTWIDGET_H
