// editsensordialog.h

#ifndef EDITSENSORDIALOG_H
#define EDITSENSORDIALOG_H

#include <QDialog>
#include <QMap>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>


namespace Model {
    class Sensore;
}

class EditSensorDialog : public QDialog {
    Q_OBJECT
public:
    EditSensorDialog(Model::Sensore* sensore, QWidget* parent = nullptr);

private slots:
    void accept() override;

private:
    Model::Sensore* originalSensor;
    std::map<std::string, QLineEdit*> editFields;
};

#endif // EDITSENSORDIALOG_H
