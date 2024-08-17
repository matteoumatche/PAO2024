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

};
}

#endif // SENSORINFOWIDGET_H

