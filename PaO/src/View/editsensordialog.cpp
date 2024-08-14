#include "editsensordialog.h"
#include <QVBoxLayout>
#include <string>
#include <set>

EditSensorDialog::EditSensorDialog(Model::Sensore* sensore,std::vector<Model::Sensore*>& sensori,QWidget* parent)
    : QDialog(parent) {

    QFormLayout* layout = new QFormLayout(this);

    // Ottieni le informazioni esistenti del sensore
    std::map<std::string, std::string> info = sensore->getInfo();
    // Definisci l'insieme delle chiavi da escludere dall'editazione
    std::set<std::string> esclusioni = {"ID", "Dato","IndiceCalore","Attivo","Tipo"};  // Esempio di chiavi da escludere

    // Crea un QLineEdit per ogni campo della mappa, se non è escluso
    for (const auto& pair : info) {
        if (esclusioni.find(pair.first) != esclusioni.end()) {
            continue;  // Salta questa chiave se è nell'insieme delle chiavi escluse
        }
        QLineEdit* edit = new QLineEdit(QString::fromStdString(pair.second), this);
        layout->addRow(QString::fromStdString(pair.first) + ":", edit);
        edits[pair.first] = edit;  // Salva il QLineEdit associato alla chiave
    }

    // Bottoni OK e Cancel
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, [this,&sensori,&sensore]{
        // Passo 1: Ottenere la mappa originale da sensore
        std::map<std::string, std::string> infoMap = sensore->getInfo();

        // Passo 2: Modificare la mappa in base alle modifiche contenute in edits
        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();
            infoMap[key] = value; // Aggiorna la mappa con i nuovi valori
        }

        // Passo 3: Convertire la mappa modificata in QJsonObject
        QJsonObject modifiedJson = MainWindow::mapToJson(infoMap);

        // Passo 4: Creare un nuovo oggetto sensore in base al tipo
        Model::Sensore* nuovoSensore= nullptr;
        std::string tipoSensore = infoMap["Tipo"];
        qWarning() <<tipoSensore;
        if (tipoSensore == "Fotocellula") {
            nuovoSensore = new Model::Fotocellula(modifiedJson);
        } else if (tipoSensore == "Temperatura") {
            nuovoSensore = new Model::Temperatura(modifiedJson);
        } else if (tipoSensore == "Temperatura Percepita") {
            nuovoSensore = new Model::TemPercepita(modifiedJson);
        } else if (tipoSensore == "Umidità") {
            nuovoSensore = new Model::Umidita(modifiedJson);
        } else if (tipoSensore == "Vento") {
            nuovoSensore = new Model::Vento(modifiedJson);
        }

        // Se l'oggetto nuovo è stato creato con successo
        if (nuovoSensore) {
            for (auto it = sensori.begin(); it != sensori.end(); ++it) {
                // Se l'ID dell'elemento corrente corrisponde all'ID del sensore da rimuovere
                if ((*it)->getID() == sensore->getID()) {
                    // Rimuoviamo l'elemento dal vettore
                    sensori.erase(it);
                    qDebug() << nuovoSensore->getInfo();
                    sensori.push_back(nuovoSensore);
                    delete(sensore);
                    // Uscire dal ciclo dopo aver rimosso l'elemento, poiché non è necessario continuare
                    break;
                }
            }

        }else qWarning() << "errore";

        accept(); // Chiude il dialogo e ritorna QDialog::Accepted
    });
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttons);
}

EditSensorDialog::~EditSensorDialog() {
    // Assicurati di eliminare i QLineEdit per evitare perdite di memoria
    for (auto& pair : edits) {
        delete pair.second; // Elimina solo i QLineEdit, non sensore
    }
}
