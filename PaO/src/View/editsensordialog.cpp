#include "editsensordialog.h"
#include "../Model/Sensore.h"
#include "../Model/Tempercepita.h"
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

        if (!(key == "Angolo" || key == "Velocita" || key == "Umidita" || key == "Temperatura" || key =="Dato"|| key =="IndiceCalore"|| key =="Attivo")) {
            QLineEdit* edit = new QLineEdit(QString::fromStdString(pair.second), this);
            if (key == "ID" || key == "Tipo") {
                edit->setReadOnly(true);
                formLayout->addRow(key + "*:", edit);
            }else{
                formLayout->addRow(key + ":", edit);
            }
            editFields[pair.first] = edit;
        }

    }


    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    formLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditSensorDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditSensorDialog::reject);
}

/*
EditSensorDialog::EditSensorDialog(Model::Sensore* sensore, QWidget* parent)
    : QDialog(parent), originalSensor(sensore) {

    setWindowTitle("Modifica Sensore");

    QFormLayout* formLayout = new QFormLayout(this);

    std::map<std::string, std::string> info = sensore->getInfo();

    for (auto& pair : info) {
        QString key = QString::fromStdString(pair.first);

        if (key == "Tipo" || key == "Nome" || key == "ID" ||key == "Dato" || key == "Angolo" || key == "Velocita" ||
            key == "Temperatura" || key == "Umidità") {
            // Non mostrare le chiavi specificate
            continue;
        }

        if (key == "Attivo") {
            // Usa una QComboBox per la chiave "Attivo"
            QComboBox* comboBox = new QComboBox(this);
            comboBox->addItem("true");
            comboBox->addItem("false");
            comboBox->setCurrentText(QString::fromStdString(pair.second));
            formLayout->addRow(key + ":", comboBox);
            editFields[pair.first] = comboBox;
        } else {
            // Usa una QLineEdit per le altre chiavi
            QLineEdit* edit = new QLineEdit(QString::fromStdString(pair.second), this);

            if (key == "ID" || key == "Tipo") {
                edit->setReadOnly(true);
            }

            formLayout->addRow(key + ":", edit);
            editFields[pair.first] = edit;
        }
    }

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    formLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditSensorDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditSensorDialog::reject);
}
*/
void EditSensorDialog::accept() {
    std::map<std::string, std::string> updatedInfo;

    for (const auto& pair : editFields) {
        QLineEdit* edit = pair.second;
        QString value = edit->text();
        updatedInfo[pair.first] = value.toStdString();
    }

    emit sensorModified(updatedInfo);
    qDebug() <<"emesso";
    QDialog::accept();
}

/*
void EditSensorDialog::accept() {
    std::map<std::string, std::string> updatedInfo;

    for (const auto& pair : editFields) {
        QWidget* widget = pair.second;
        QString value;

        // Usa qobject_cast per determinare il tipo di widget e ottenere il valore
        if (auto* lineEdit = qobject_cast<QLineEdit*>(widget)) {
            value = lineEdit->text();
        } else if (auto* comboBox = qobject_cast<QComboBox*>(widget)) {
            value = comboBox->currentText();
        }

        updatedInfo[pair.first] = value.toStdString();
    }

    emit sensorModified(updatedInfo);
    qDebug() << "emesso";
    QDialog::accept();
}*/
