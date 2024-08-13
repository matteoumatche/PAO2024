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



public:
    SensorListWidget(std::vector<Model::Sensore*>& sensori, QWidget* parent = nullptr);

signals:
    void sensorClicked(Model::Sensore* sensore); // Segnale emesso quando un sensore viene cliccato
    void updateList(); //emesso quando i dati dei sensori cambiano
    void clonato(Model::Sensore* sensore); //emesso quando i dati dei sensori cambiano
private slots:
    void sendRequestUpdateList();

};
}
#endif // SENSORLISTWIDGET_H
