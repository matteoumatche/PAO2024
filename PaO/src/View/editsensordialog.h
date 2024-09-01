#ifndef EDITSENSORDIALOG_H
#define EDITSENSORDIALOG_H

#include "../Model/Sensore.h"

#include <QDialog>
#include <QLineEdit>

class EditSensorDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditSensorDialog(Model::Sensore* sensore, QWidget* parent = nullptr);

signals:
    void sensorModified(std::map<std::string, std::string>&);

protected:
    void accept() override;

private:
    Model::Sensore* originalSensor;
    std::map<std::string, QLineEdit*> editFields;
};


#endif
