#include "editsensordialog.h"
#include "../Model/Sensore.h"
#include "../mainwindow.h"

#include <QFormLayout>
#include <QDialogButtonBox>

EditSensorDialog::EditSensorDialog(Model::Sensore* sensore, QWidget* parent)
    : QDialog(parent), originalSensor(sensore) {

    setWindowTitle("Modifica Sensore");

    QFormLayout* formLayout = new QFormLayout(this);

    std::map<std::string, std::string> info = sensore->getInfo();

    for (auto& pair : info) {
        QString key = QString::fromStdString(pair.first);

               //mostra solo i campi modificabili
               if (key == "ID" || key == "Tipo" || key == "Angolo" || key == "Umidità" || key == "Temperatura" || key == "Indice Calore"
                || key == "Dato" || key == "MaxVelocita" || key == "Velocità") {
                   continue; //salta i campi non modificabili
               }

               QLineEdit* edit = new QLineEdit(QString::fromStdString(pair.second), this);
               formLayout->addRow(key + ":", edit);
               editFields[pair.first] = edit;
    }

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    formLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditSensorDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditSensorDialog::reject);
}

void EditSensorDialog::accept() {
    std::map<std::string, std::string> updatedInfo = originalSensor->getInfo();

    for (const auto& pair : editFields) {
        QLineEdit* edit = pair.second;
        QString value = edit->text();
        updatedInfo[pair.first] = value.toStdString();
    }

    emit sensorModified(updatedInfo);
    QDialog::accept();
}
