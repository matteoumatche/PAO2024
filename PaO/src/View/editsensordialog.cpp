// editsensordialog.cpp

#include "editsensordialog.h"
#include "../Model/sensore.h"


EditSensorDialog::EditSensorDialog(Model::Sensore* sensore, QWidget* parent)
    : QDialog(parent), originalSensor(sensore) {

    setWindowTitle("Modifica Sensore");

    QFormLayout* formLayout = new QFormLayout(this);

    std::map<std::string, std::string> info = sensore->getInfo();

    for (auto& pair : info) {
        QString key = QString::fromStdString(pair.first);
        if (key == "ID" || key == "Tipo") continue;

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
    // Crea una mappa per memorizzare le informazioni aggiornate
    std::map<std::string, std::string> updatedInfo;

    // Cicla attraverso i campi di modifica e raccogli i dati
    for (const auto& pair : editFields) {
        QLineEdit* edit = pair.second;
        QString value = edit->text();
        updatedInfo[pair.first] = value.toStdString();
    }

    // Aggiorna le informazioni del sensore esistente
    if (originalSensor) {
        //originalSensor->updateInfo(updatedInfo);
    }

    // Conferma e chiudi il dialogo
    QDialog::accept();
}
