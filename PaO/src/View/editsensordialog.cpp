#include "editsensordialog.h"
#include <QVBoxLayout>
#include <string>
#include <set>

EditSensorDialog::EditSensorDialog(Model::Sensore* sensore,std::vector<Model::Sensore*>& sensori,QWidget* parent)
    : QDialog(parent) {
    qDebug() << "1";
    QFormLayout* layout = new QFormLayout(this);
    qDebug() << "2";
    // Ottieni le informazioni esistenti del sensore
    std::map<std::string, std::string> info = sensore->getInfo();
    qDebug() << "3";
    // Definisci l'insieme delle chiavi da escludere dall'editazione
    qDebug() << "4";
    std::set<std::string> esclusioni = {"ID", "Dato","IndiceCalore","Attivo","Tipo"};  // Esempio di chiavi da escludere
    qDebug() << "5";
    // Crea un QLineEdit per ogni campo della mappa, se non è escluso
    for (const auto& pair : info) {
        if (esclusioni.find(pair.first) != esclusioni.end()) {
            continue;  // Salta questa chiave se è nell'insieme delle chiavi escluse
        }
        QLineEdit* edit = new QLineEdit(QString::fromStdString(pair.second), this);
        layout->addRow(QString::fromStdString(pair.first) + ":", edit);
        edits[pair.first] = edit;  // Salva il QLineEdit associato alla chiave
    }
qDebug() << "6";
    // Bottoni OK e Cancel
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, [this,&sensori,sensore]{
        qDebug() << "conn 1";
        // Passo 1: Ottenere la mappa originale da sensore
        std::map<std::string, std::string> infoMap = sensore->getInfo();
        qDebug() << "passo 1";
        // Passo 2: Modificare la mappa in base alle modifiche contenute in edits
        for (const auto& pair : edits) {
            const std::string& key = pair.first;
            const std::string& value = pair.second->text().toStdString();
            infoMap[key] = value; // Aggiorna la mappa con i nuovi valori
        }

        // Passo 3: Convertire la mappa modificata in QJsonObject
        QJsonObject modifiedJson = MainWindow::mapToJson(infoMap);
        qDebug() << "passo 4";
        // Passo 4: Creare un nuovo oggetto sensore in base al tipo
        Model::Sensore* nuovoSensore= nullptr;
        qDebug() << "passo 5";
        std::string tipoSensore = infoMap["Tipo"];
        qDebug() << "passo 6";
        //qWarning() <<tipoSensore;
        if (tipoSensore == "Fotocellula") {
           qDebug() << "F";
            Model::Fotocellula* _nuovoSensore = new Model::Fotocellula(modifiedJson);
            nuovoSensore= _nuovoSensore;

        } else if (tipoSensore == "Temperatura") {
            qDebug() << "T";
            Model::Temperatura* _nuovoSensore = new Model::Temperatura(modifiedJson);
            nuovoSensore= _nuovoSensore;

        } else if (tipoSensore == "TempPercepita") {
            qDebug() << "TP";
            Model::TemPercepita* _nuovoSensore = new Model::TemPercepita(modifiedJson);
            nuovoSensore= _nuovoSensore;
            qDebug() << "TP";
        } else if (tipoSensore == "Umidità") {
            qDebug() << "U";
            Model::Umidita* _nuovoSensore = new Model::Umidita(modifiedJson);
            nuovoSensore= _nuovoSensore;
            qDebug() << "U";
        } else if (tipoSensore == "Vento") {
            qDebug() << "V";
            Model::Vento* _nuovoSensore = new Model::Vento(modifiedJson);
            nuovoSensore= _nuovoSensore;
            qDebug() << "V";
        }

        // Se l'oggetto nuovo è stato creato con successo
        if (nuovoSensore) {
            for (auto it = sensori.begin(); it != sensori.end(); ++it) {
                // Se l'ID dell'elemento corrente corrisponde all'ID del sensore da rimuovere
                if ((*it)->getID() == sensore->getID()) {
                    // Rimuoviamo l'elemento dal vettore
                    sensori.erase(it);
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
void EditSensorDialog::acceptChanges(Model::Sensore* s){}

EditSensorDialog::~EditSensorDialog() {
    // Assicurati di eliminare i QLineEdit per evitare perdite di memoria
    for (auto& pair : edits) {
        delete pair.second; // Elimina solo i QLineEdit, non sensore
    }
}
