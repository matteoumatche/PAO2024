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

    // Campi aggiuntivi per Vento
    if (dynamic_cast<Model::Vento*>(sensore)) {
        // Creare QLineEdit aggiuntivi per i valori di Dato
        valore1LineEdit = new QLineEdit(this);
        valore2LineEdit = new QLineEdit(this);

        layout->addRow("Primo valore Dato:", valore1LineEdit);
        layout->addRow("Secondo valore Dato:", valore2LineEdit);
    }

    // Bottoni OK e Cancel
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &EditSensorDialog::acceptChanges);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttons);
}

void EditSensorDialog::acceptChanges() {
    // Verifica il tipo di sensore all'inizio
    if (auto fotocellula = dynamic_cast<Model::Fotocellula*>(sensore)) {
        // Gestione specifica per Fotocellula
        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                fotocellula->setNome(value);
            } else if (key == "ID") {
                fotocellula->setID(std::stoul(value));
            } else if (key == "Soglia") {
                fotocellula->setSoglia(std::stod(value));
            } else if (key == "Tolleranza") {
                fotocellula->setTolleranza(std::stod(value));
            }
        }
    } else if (auto temperatura = dynamic_cast<Model::Temperatura*>(sensore)) {
        // Gestione specifica per Temperatura
        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                temperatura->setNome(value);
            } else if (key == "ID") {
                temperatura->setID(std::stoul(value));
            } else if (key == "Tolleranza") {
                temperatura->setTolleranza(std::stod(value));
            } else if (key == "Dato") {
                temperatura->setDato(std::stod(value));
            }
        }
    } else if (auto temPercepita = dynamic_cast<Model::TemPercepita*>(sensore)) {
        // Gestione specifica per TemPercepita
        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                temPercepita->setNome(value);
            } else if (key == "ID") {
                temPercepita->setID(std::stoul(value));
            } else if (key == "IndiceCalore") {
                temPercepita->setIndiceCalore(std::stod(value));
            }
        }
    } else if (auto umidita = dynamic_cast<Model::Umidita*>(sensore)) {
        // Gestione specifica per Umidita
        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                umidita->setNome(value);
            } else if (key == "ID") {
                umidita->setID(std::stoul(value));
            } else if (key == "Tolleranza") {
                umidita->setTolleranza(std::stod(value));
            } else if (key == "Dato") {
                umidita->setDato(std::stod(value));
            }
        }
    } else if (auto vento = dynamic_cast<Model::Vento*>(sensore)) {
        // Gestione specifica per Vento
        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();

            if (key == "Nome") {
                vento->setNome(value);
            } else if (key == "ID") {
                vento->setID(std::stoul(value));
            } else if (key == "MaxVelocita") {
                vento->setMaxVelocita(std::stod(value));
            } else if (key == "Offset") {
                vento->setOffset(std::stod(value));
            } else if (key == "TolleranzaGoniometro") {
                vento->setTolleranzaGoniometro(std::stod(value));
            } else if (key == "TolleranzaAnemometro") {
                vento->setTolleranzaAnemometro(std::stod(value));
            }
        }

        vento->setDato(valore1LineEdit->text().toDouble(), valore2LineEdit->text().toDouble());
    }

    accept();  // Chiude il dialogo e ritorna QDialog::Accepted
}
