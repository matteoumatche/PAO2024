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
    void sensorSelected(const std::map<std::string, std::string>& sensorInfo); // Segnale con informazioni del sensore

private:
    std::map<std::string, std::string> m_sensorInfo; // Memorizza le informazioni del sensore

    void mousePressEvent(QMouseEvent* event) override; // Override per gestire i click
};
}

#endif // SENSORINFOWIDGET_H

