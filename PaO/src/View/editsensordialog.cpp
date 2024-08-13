#include "editsensordialog.h"
#include <QVBoxLayout>

EditSensorDialog::EditSensorDialog(Model::Sensore* sensore, QWidget* parent)
    : QDialog(parent), sensore(sensore) {

    QFormLayout* layout = new QFormLayout(this);

    // Ottieni le informazioni esistenti del sensore
    std::map<std::string, std::string> info = sensore->getInfo();

    // Crea un QLineEdit per ogni campo della mappa, e memorizzalo in un'altra mappa
    for (const auto& pair : info) {
        QLineEdit* edit = new QLineEdit(QString::fromStdString(pair.second), this);
        layout->addRow(QString::fromStdString(pair.first) + ":", edit);
        edits[pair.first] = edit;  // Salva il QLineEdit associato alla chiave
    }

    // Bottoni OK e Cancel
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &EditSensorDialog::acceptChanges);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttons);
}

void EditSensorDialog::acceptChanges() {

    std::string tipoSensore = sensore->getInfo()["type"];

    if (tipoSensore == "Fotocellula") {

        Model::Fotocellula* f = static_cast<Model::Fotocellula*>(sensore);

        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                sensore->setNome(value);
            } else if (key == "Soglia") {
                f->setSoglia(std::stod(value));
            } else if (key == "Tolleranza") {
                f->setTolleranza(std::stod(value));
            }
        }

    } else if (tipoSensore == "Temperatura") {

        Model::Temperatura* t = static_cast<Model::Temperatura*>(sensore);

        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                t->setNome(value);
            } else if (key == "Tolleranza") {
                t->setTolleranza(std::stod(value));
            }
        }

    } else if (tipoSensore == "Temperatura Percepita") {

        Model::TemPercepita* tp = static_cast<Model::TemPercepita*>(sensore);

        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                tp->setNome(value);
            }
        }

    } else if (tipoSensore == "Umidità") {

        Model::Umidita* u = static_cast<Model::Umidita*>(sensore);

        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                u->setNome(value);
            } else if (key == "Tolleranza") {
                u->setTolleranza(std::stod(value));
            }
        }

    } else if (tipoSensore == "Vento") {

        Model::Vento* v = static_cast<Model::Vento*>(sensore);

        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                v->setNome(value);
            } else if (key == "Offset") {
                v->setOffset(std::stod(value));
            } else if (key == "TolleranzaGoniometro") {
                v->setTolleranzaGoniometro(std::stod(value));
            } else if (key == "TolleranzaAnemometro") {
                v->setTolleranzaAnemometro(std::stod(value));
            }
        }
    }

    accept();  // Chiude il dialogo e ritorna QDialog::Accepted
}
