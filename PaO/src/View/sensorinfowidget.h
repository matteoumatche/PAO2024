#ifndef SENSORINFOWIDGET_H
#define SENSORINFOWIDGET_H

#include <QWidget>
#include <map>
#include <string>
#include "../Model/sensore.h"

namespace View{

class SensorInfoWidget : public QWidget {
    Q_OBJECT
public:
    SensorInfoWidget(const std::map<std::string, std::string>& info, QWidget* parent = nullptr);

signals:
    void widgetClicked(Model::Sensore* sensore); // Segnale emesso quando il widget viene cliccato

protected:
    void mousePressEvent(QMouseEvent* event, Model::Sensore* sensore); // Sovrascrittura del metodo per gestire il clic
};

}

#endif // SENSORINFOWIDGET_H

