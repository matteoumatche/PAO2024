#include "editsensordialog.h"
#include "../Model/Sensore.h"
#include "../Model/Tempercepita.h"
#include "../mainwindow.h"

#include <QFormLayout>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>

EditSensorDialog::EditSensorDialog(Model::Sensore* sensore, QWidget* parent)
    : QDialog(parent), originalSensor(sensore) {

    setWindowTitle("Modifica Sensore");

    QFormLayout* formLayout = new QFormLayout(this);

    std::map<std::string, std::string> info = sensore->getInfo();

    for (auto& pair : info) {
        QString key = QString::fromStdString(pair.first);

        if (!(key == "Angolo" || key == "Velocita" || key == "Umidita" || key == "Temperatura" || key =="Dato"|| key =="IndiceCalore"|| key =="Attivo")) {
            if(key=="Tolleranza"|| key=="MaxVelocita" || key=="TolleranzaAnemometro" || key=="TolleranzaGoniometro" ||key=="Offset"){
                QDoubleSpinBox* spinBox = new QDoubleSpinBox();
                spinBox->setValue(QString::fromStdString(pair.second).toDouble());

                if(key=="Tolleranza" || key=="TolleranzaAnemometro"){
                    spinBox->setRange(0, 10);
                    spinBox->setDecimals(3);
                }else if(key=="TolleranzaAnemometro"){
                    spinBox->setRange(0, 90);
                    spinBox->setDecimals(3);
                }else if(key=="MaxVelocita"){
                spinBox->setRange(0, 1000);
                spinBox->setDecimals(2);
                }else if(key=="Offset"){
                    spinBox->setRange(0, 180);
                    spinBox->setDecimals(2);
                }
                formLayout->addRow(key + ":", spinBox);
                editFields[pair.first] = spinBox;
            }else{
                QLineEdit* edit = new QLineEdit(QString::fromStdString(pair.second));
                if (key == "ID" || key == "Tipo") {
                    edit->setReadOnly(true);
                    formLayout->addRow(key + "*:", edit);
                }else{
                    formLayout->addRow(key + ":", edit);
                }
                editFields[pair.first] = edit;
            }
        }
    }


    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    formLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditSensorDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditSensorDialog::reject);
}

void EditSensorDialog::accept() {
    std::map<std::string, std::string> updatedInfo;

    for (const auto& pair : editFields) {
        QWidget* widget = pair.second;
        QString value;

        // Verifica se il widget è un QDoubleSpinBox
        if (QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(widget)) {
            value = QString::number(spinBox->value(), 'f', spinBox->decimals());
        }
        // Altrimenti, trattalo come QLineEdit
        else if (QLineEdit* edit = qobject_cast<QLineEdit*>(widget)) {
            value = edit->text();
        }

        updatedInfo[pair.first] = value.toStdString();
    }

    emit sensorModified(updatedInfo);
    qDebug() <<"emesso";
    QDialog::accept();
}

