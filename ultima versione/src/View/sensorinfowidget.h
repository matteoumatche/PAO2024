#ifndef SENSORINFOWIDGET_H
#define SENSORINFOWIDGET_H

#include <QWidget>

namespace View{

class SensorInfoWidget : public QWidget {
    Q_OBJECT

public:
    SensorInfoWidget(const std::map<std::string, std::string>& info, QWidget* parent = nullptr);

signals:
    void sensorSelected(const std::string& sensorID);

private:
    std::string sensorID;

    void mousePressEvent(QMouseEvent* event) override;
};

}

#endif

