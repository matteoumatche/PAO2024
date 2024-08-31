#include "mainwindow.h"
#include "Model/fotocellula.h"
#include "Model/temperatura.h"
#include "Model/vento.h"
#include "Model/umidita.h"
#include "Model/tempercepita.h"
#include "View/widgetfotocellula.h"
#include "View/widgettemperatura.h"
#include "View/widgettempercepita.h"
#include "View/widgetumidita.h"
#include "View/widgetvento.h"
#include "View/widgetgrafico.h"
#include "View/editsensordialog.h"
#include "View/optionsWidget.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QFormLayout>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mainLayout(nullptr), centralLayout(nullptr), centralWidget(nullptr),sensorListWidget(nullptr)
{
    setWindowTitle("Greenhouse manager");

    resize(1280, 720); // Large initial size

    //layout
    mainLayout = new QVBoxLayout;           //layout principale: contiene Toolbar e centalLayout
    centralLayout = new QHBoxLayout;        //layout sotto Toolbar: contiene sensorWidgetLayout e graphWidget
    sensorWidgetLayout = new QVBoxLayout;   //layout della lista: contiene sensorListWidget e searchLayout
    searchLayout = new QHBoxLayout;         //layout della barra di ricerca: contiene barra e bottone
    graphLayout = new QVBoxLayout;          //layout della zona a destra della lista: contiene graphWidget e optionsLayout

    //toolbar e widget
    centralWidget = new QWidget(nullptr);
    tbar= new View::ToolBar;
    sensorListWidget= new View::SensorListWidget(sensori,nullptr);
    graphWidget = new View::WidgetGrafico(nullptr);
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("Cerca sensori per nome...");
    opzioni = nullptr;
    filterComboBox = new QComboBox(this);
    filterComboBox->addItem("Tutti");  // Aggiungi un'opzione per mostrare tutti i sensori
    filterComboBox->addItems(getAvailableSensorTypes());  // Aggiungi i tipi di sensori disponibili
    searchLayout->addWidget(filterComboBox);

    // Area di scorrimento per la lista dei sensori
    scrollArea = new QScrollArea;
    scrollArea->setWidget(sensorListWidget);

    //IMPOSTAZIONI LAYOUT--------------------------------

    //mainLayout
    mainLayout->addWidget(tbar);
    mainLayout->addLayout(centralLayout);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    //centralLayout
    centralLayout->addLayout(sensorWidgetLayout);
    centralLayout->addLayout(graphLayout);

    //sensorWidgetLayout
    sensorWidgetLayout->addWidget(scrollArea);
    sensorWidgetLayout->addLayout(searchLayout);

    //searchLayout
    searchLayout->addWidget(searchLineEdit);

    //---------------------------------------------------

    //misure
    tbar->setMinimumSize(1024, 30);
    sensorListWidget->setMinimumSize(300, 400);
    centralLayout->setStretchFactor(sensorListWidget, 2);
    centralLayout->setStretchFactor(graphLayout, 2);
    graphWidget->adjustSize();

    // Connessione dei segnali di ToolBar agli slot di MainWindow
    connect(sensorListWidget, &View::SensorListWidget::updateList, this, &MainWindow::dataUpdated);
    connect(tbar, &View::ToolBar::newSignal, this, &MainWindow::showNewSensorDialog);
    connect(tbar, &View::ToolBar::openSignal, this, &MainWindow::openJsonFile);
    connect(tbar, &View::ToolBar::saveSignal, this, &MainWindow::saveJsonFile);
    connect(tbar, &View::ToolBar::saveAsSignal, this, &MainWindow::saveJsonFileAs);
    connect(tbar, &View::ToolBar::newSignal, this, &MainWindow::dataUpdated);
    connect(tbar, &View::ToolBar::openSignal, this, &MainWindow::dataUpdated);
    connect(sensorListWidget, &View::SensorListWidget::updateList, this, &MainWindow::dataUpdated);
    connect(sensorListWidget, &View::SensorListWidget::sensorSelected, this, &MainWindow::onSensorSelected);
    connect(searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(filterComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onFilterComboBoxChanged);

}

MainWindow::~MainWindow(){}

void MainWindow::showNewSensorDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Nuovo Sensore");

    QFormLayout* formLayout= new QFormLayout();
    QVBoxLayout *dialogLayout = new QVBoxLayout(&dialog);

    QLineEdit *nameEdit = new QLineEdit;
    QComboBox *typeComboBox = new QComboBox(&dialog);
    QLineEdit *idEdit = new QLineEdit(&dialog);

    QStringList sensorTypes = getAvailableSensorTypes();
    typeComboBox->addItems(sensorTypes);

    formLayout->addRow("Tipo:", typeComboBox);
    formLayout->addRow("ID:", idEdit);
    formLayout->addRow("Nome:", nameEdit);

    dialogLayout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    dialogLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, [this, &dialog, typeComboBox, idEdit, nameEdit]() {
        QString type = typeComboBox->currentText();
        QString id = idEdit->text();
        QString name = nameEdit->text();

        if (id.isEmpty() || name.isEmpty()) {
            QMessageBox::warning(&dialog, "Errore", "I campi 'ID' e 'Nome' devono essere riempiti.");
            return;
        }

        //validazione dell'ID
        QRegularExpression idRegex("^[0-9]{4}$");
        if (!idRegex.match(id).hasMatch()) {
            QMessageBox::warning(&dialog, "Errore", "L'ID deve avere esattamente 4 caratteri numerici.");
            return;
        }

        //validazione del Nome
        QRegularExpression nameRegex("^[A-Za-z0-9]+$"); //solo caratteri alfabetici
        if (!nameRegex.match(name).hasMatch()) {
            QMessageBox::warning(&dialog, "Errore", "Il Nome deve contenere solo caratteri alfanumerici.");
            return;
        }

        addSensor(type, id, name);
        dialog.accept();
    });

    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    dialog.exec();
}

void MainWindow::addSensor(const QString &type, const QString &id, const QString &name){
    //controllo ID o nome già esistenti
    for (const auto& sensore : sensori) {
        if (sensore->getID() == id.toUInt() || sensore->getNome() == name.toStdString()) {
            QMessageBox::warning(this, "Errore", "ID o Nome già esistenti. Inserire valori unici.");
            return;
        }
    }

    Model::Sensore* nuovoSensore = nullptr;

    if (type == "Fotocellula") {
        nuovoSensore = new Model::Fotocellula(id.toUInt(), name.toStdString());
    } else if (type == "Vento") {
        nuovoSensore = new Model::Vento(id.toUInt(), name.toStdString());
    } else if (type == "Temperatura") {
        nuovoSensore = new Model::Temperatura(id.toUInt(), name.toStdString());
    } else if (type == "Umidità") {
        nuovoSensore = new Model::Umidita(id.toUInt(), name.toStdString());
    } else if (type == "Temp. Percepita") {
        nuovoSensore = new Model::TemPercepita(id.toUInt(), name.toStdString());
    }

    if (nuovoSensore) {
        if (type == "Fotocellula") {
            //è una fotocellula: aggiunge alla fine della lista
            sensori.push_back(nuovoSensore);
        } else {
            //non è fotocellula: inserisce prima delle fotocellule
            auto it = std::find_if(sensori.begin(), sensori.end(), [](const Model::Sensore* s) {
                return dynamic_cast<const Model::Fotocellula*>(s) != nullptr;
            });

            sensori.insert(it, nuovoSensore);
        }
    }

    QMessageBox::information(this, "Sensore Aggiunto", "Tipo: " + type + "\nID: " + id + "\nNome: " + name);
    tbar->activateSaveAction();
    tbar->activateSaveAsAction();

}

QStringList MainWindow::getAvailableSensorTypes() {
    return QStringList() << "Fotocellula" << "Vento" << "Temperatura" << "Umidità" << "Temp. Percepita";
}

Model::Sensore* MainWindow::creaSensore(const QJsonObject& info)  {
    QString tipo = info["Tipo"].toString();

    if (!tipo.isEmpty()) {
        if (tipo == "Fotocellula") {
            return new Model::Fotocellula(info);
        } else if (tipo == "Temperatura") {
            return new Model::Temperatura(info);
        }else if (tipo == "Vento") {
            return new Model::Vento(info);
        }else if (tipo == "Umidità") {
            return new Model::Umidita(info);
        }else if (tipo == "Temp. Percepita") {
            return new Model::TemPercepita(info);
        }

    }
    return nullptr;
}

QJsonObject MainWindow::mapToJson(const std::map<std::string, std::string>& info) {
    QJsonObject jsonObject;
    for (const auto& pair : info) {
        jsonObject[QString::fromStdString(pair.first)] = QString::fromStdString(pair.second);
    }
    return jsonObject;
}

void MainWindow::openJsonFile(){
    QString nomeFile = QFileDialog::getOpenFileName(this, tr("Apri file JSON"), "", tr("JSON Files (*.json);;All Files (*)"));

    if (nomeFile.isEmpty()) {
        return;
    }

    QFile file(nomeFile);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Errore"), tr("Non è stato possibile aprire il file."));
        return;
    }

    QByteArray json = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(json);
    if (doc.isNull() || !doc.isObject()) {
        QMessageBox::warning(this, tr("Errore"), tr("Formato del file JSON non valido."));
        return;
    }

    QJsonObject rootObject = doc.object();
    QJsonArray arraySensori = rootObject["sensori"].toArray();

    //pulizia dei sensori esistenti
    sensori.clear();

    for (const QJsonValue& i : arraySensori) {
        QJsonObject sen_obj = i.toObject();

        Model::Sensore* sensore = creaSensore(sen_obj);
        if (sensore) {
            sensori.push_back(sensore);
        } else {
            qWarning() << "Tipo di sensore non riconosciuto o errore nella creazione.";
        }
    }

    pathToFile = nomeFile;
    tbar->activateSaveAction();
    tbar->activateSaveAsAction();
}

void MainWindow::saveJsonFile(){
    if (pathToFile.isEmpty()) {
        saveJsonFileAs();  //se non c'è un file aperto, richiama saveJsonFileAs()
        return;
    }

    QFile file(pathToFile);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Errore"), tr("Non è stato possibile aprire il file per la scrittura."));
        return;
    }

    QJsonArray arraySensori;
    for (const auto& sensore : sensori) {
        QJsonObject sensorObject = mapToJson(sensore->getInfo());
        arraySensori.append(sensorObject);
    }

    QJsonObject rootObject;
    rootObject["sensori"] = arraySensori;

    QJsonDocument doc(rootObject);
    file.write(doc.toJson());
    file.close();

}

void MainWindow::saveJsonFileAs(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva file JSON"), "", tr("JSON Files (*.json)"));

    if (fileName.isEmpty()) {
        return;
    }

    //aggiungi l'estensione .json se non è presente
    if (!fileName.endsWith(".json", Qt::CaseInsensitive)) {
        fileName += ".json";
    }

    pathToFile = fileName;
    saveJsonFile();
}

void MainWindow::dataUpdated() {
    qDebug() << "dataUpdated";

    //prima di creare un nuovo widget, eliminiamo il vecchio
    if (sensorListWidget) {
        delete sensorListWidget;
        sensorListWidget = nullptr;
    }

    // Ordina i sensori in modo che i Fotocellula siano alla fine
    std::sort(sensori.begin(), sensori.end(), [](Model::Sensore* a, Model::Sensore* b) {
        auto isFotocellulaA = dynamic_cast<Model::Fotocellula*>(a) != nullptr;
        auto isFotocellulaB = dynamic_cast<Model::Fotocellula*>(b) != nullptr;
        return isFotocellulaA < isFotocellulaB; // Fotocellula deve essere "più grande" di tutti gli altri
    });

    //ricrea il widget con la lista aggiornata
    sensorListWidget = new View::SensorListWidget(sensori, this);
    scrollArea->setWidget(sensorListWidget);

    //riconnetti i segnali
    connect(sensorListWidget, &View::SensorListWidget::updateList, this, &MainWindow::dataUpdated);
    connect(sensorListWidget, &View::SensorListWidget::sensorSelected, this, &MainWindow::onSensorSelected);
}

void MainWindow::reloadJsonFile() {
    if (pathToFile.isEmpty()) {
        return;
    }

    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Errore"), tr("Non è stato possibile aprire il file."));
        return;
    }

    QByteArray json = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(json);
    if (doc.isNull() || !doc.isObject()) {
        QMessageBox::warning(this, tr("Errore"), tr("Formato del file JSON non valido."));
        return;
    }

    QJsonObject rootObject = doc.object();
    QJsonArray arraySensori = rootObject["sensori"].toArray();

    sensori.clear();

    for (const QJsonValue& i : arraySensori) {
        QJsonObject sen_obj = i.toObject();
        Model::Sensore* sensore = creaSensore(sen_obj);
        if (sensore) {
            sensori.push_back(sensore);
        } else {
            qWarning() << "Tipo di sensore non riconosciuto o errore nella creazione.";
        }
    }

    //ricarica la lista dei sensori
    sensorListWidget = new View::SensorListWidget(sensori, this); //ricrea il widget
    scrollArea->setWidget(sensorListWidget); //aggiorna l'area di scorrimento

    tbar->activateSaveAction();
    tbar->activateSaveAsAction();
}

void MainWindow::onSensorSelected(const std::string sensorID) {

    if (titoloLabel) {
        graphLayout->removeWidget(titoloLabel);
        delete titoloLabel;
        titoloLabel = nullptr;
    }

    if (graphWidget) {
        delete graphWidget;
        graphWidget = nullptr;
    }

    if (opzioni) {
        delete opzioni;
        opzioni = nullptr;
    }

    Model::Sensore* selectedSensor = nullptr;
    for (Model::Sensore* sensore : sensori) {
        if (std::to_string(sensore->getID()) == sensorID) {
            selectedSensor = sensore;
            break;
        }
    }

    if (!selectedSensor) {
        qDebug() << "Errore: nessun sensore trovato";
        return;
    }

    opzioni = new View::optionsWidget(selectedSensor, nullptr);
    std::map<std::string, std::string> info = selectedSensor->getInfo();

    //widget del titolo
    QString titolo = QString("%1 - %2")
                      .arg(QString::fromStdString(selectedSensor->getNome()))
                      .arg(QString::number(selectedSensor->getID()));
    titoloLabel = new QLabel(titolo, this);
    titoloLabel->setAlignment(Qt::AlignCenter);

    //QSizePolicy per il titolo
    titoloLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titoloLabel->setMinimumHeight(30);  //altezza minima del titolo
    titoloLabel->setMaximumHeight(30);  //altezza massima del titolo

    //dimensione del font
    QFont font = titoloLabel->font();
    font.setPointSize(12);
    font.setBold(true);
    titoloLabel->setFont(font);

    graphLayout->addWidget(titoloLabel);

    if (info["Tipo"] == "Vento") {
        graphWidget = new View::WidgetVento(selectedSensor, this);
    } else if (info["Tipo"] == "Temperatura") {
        graphWidget = new View::WidgetTemperatura(selectedSensor, this);
    } else if (info["Tipo"] == "Umidità") {
        graphWidget = new View::WidgetUmidita(selectedSensor, this);
    } else if (info["Tipo"] == "Temp. Percepita") {
        graphWidget = new View::WidgetTempercepita(this);
    } else if (info["Tipo"] == "Fotocellula") {
        graphWidget = new View::WidgetFotocellula(&sensori, this);
    } else {
        graphWidget = new View::WidgetGrafico(this);
    }

    connect(opzioni, &View::optionsWidget::onCloneClicked, graphWidget, [this,selectedSensor]{
        cloneSensor(selectedSensor);
    });

    connect(opzioni, &View::optionsWidget::onModifyClicked, graphWidget, [this,selectedSensor]{
        modifySensor(selectedSensor);
    });

    connect(opzioni, &View::optionsWidget::onDeleteClicked, graphWidget, [this,selectedSensor]{
        deleteSensor(selectedSensor);
    });

    connect(opzioni, &View::optionsWidget::onSimulaClicked, graphWidget, [this,selectedSensor]{
        graphWidget->simulazione(selectedSensor);
    });

    graphLayout->addWidget(graphWidget);
    graphLayout->addWidget(opzioni);

    opzioni->setMaximumSize(1600, 200);
}

void MainWindow::cloneSensor(Model::Sensore* selectedSensor){
    if (selectedSensor) {
        // Clona il sensore selezionato
        Model::Sensore* clonedSensor = selectedSensor->clone();

        // Ottieni l'ID originale e creane uno nuovo
        int newID = selectedSensor->getID();

        // Funzione lambda per incrementare l'ID seguendo la logica specificata
        auto incrementID = [](int id) -> int {
            std::string idStr = std::to_string(id);
            while (idStr.length() < 4) {
                idStr = "0" + idStr;
            }
            for (int i = 3; i >= 0; --i) {
                if (idStr[i] == '9') {
                    idStr[i] = '0';
                } else {
                    idStr[i]++;
                    break;
                }
            }
            return std::stoi(idStr);
        };

        // Trova un ID unico per il clone
        bool idExists;
        do {
            newID = incrementID(newID);
            idExists = std::any_of(sensori.begin(), sensori.end(),
                                   [newID](Model::Sensore* sensore) {
                                       return sensore->getID() == newID;
                                   });
        } while (idExists);

        // Imposta il nuovo ID al sensore clonato
        clonedSensor->setID(newID);

        // Aggiungi il clone alla lista dei sensori
        sensori.push_back(clonedSensor);

        // Aggiorna la visualizzazione
        emit sensorListWidget->updateList();
    }
}


/*
void MainWindow::cloneSensor(Model::Sensore* selectedSensor){
    if (selectedSensor) {
        //clona il sensore selezionato
        Model::Sensore* clonedSensor = selectedSensor->clone();

        //aggiungi il clone alla lista dei sensori
        sensori.push_back(clonedSensor);

        //aggiorna la visualizzazione
        emit sensorListWidget->updateList();
    }
}
*/

void MainWindow::modifySensor(Model::Sensore* selectedSensor) {
    if (selectedSensor) {
        EditSensorDialog* dialog = new EditSensorDialog(selectedSensor, this);

        connect(dialog, &EditSensorDialog::sensorModified, this, &MainWindow::onSensorModified);

        if (dialog->exec() == QDialog::Accepted) {
            qDebug() <<"accettato";
            emit sensorListWidget->updateList();
            onSensorSelected(selectedSensor->getInfo()["ID"]);
        }

        disconnect(dialog, &EditSensorDialog::sensorModified, this, &MainWindow::onSensorModified);
    }
}

void MainWindow::deleteSensor(Model::Sensore* selectedSensor){
    if (selectedSensor) {
        // Mostra un QMessageBox per confermare l'eliminazione
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Conferma eliminazione",
                                      "Sei sicuro di voler eliminare il sensore selezionato?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // Trova ed elimina il sensore selezionato
            auto it = std::find_if(sensori.begin(), sensori.end(),
                                   [&selectedSensor](Model::Sensore* sensore) {
                                       return sensore->getID() == selectedSensor->getID();
                                   });
            if (it != sensori.end()) {
                delete *it;
                sensori.erase(it);
                selectedSensor = nullptr;
            }

            // Aggiorna la visualizzazione
            emit sensorListWidget->updateList();
            onSensorSelected("eliminato");
        } else {
            // Se l'utente ha selezionato "No", non fare nulla
            return;
        }
    }
}


void MainWindow::onSearchTextChanged(const QString& searchText) {
    std::vector<Model::Sensore*> filteredSensors;

    // Ottieni il tipo di sensore selezionato dalla QComboBox
    QString selectedType = filterComboBox->currentText();

    for (const auto& sensor : sensori) {
        bool matchesSearchText = QString::fromStdString(sensor->getNome()).contains(searchText, Qt::CaseInsensitive);

        bool matchesType = true;
        if (selectedType != "Tutti") {
            QString sensorType = QString::fromStdString(sensor->getInfo()["Tipo"]);
            matchesType = (sensorType == selectedType);
        }

        if (matchesSearchText && matchesType) {
            filteredSensors.push_back(sensor);
        }
    }

    updateSensorList(filteredSensors);
}

void MainWindow::onFilterComboBoxChanged(const QString& sensorType) {
    std::vector<Model::Sensore*> filteredSensors;

    if (sensorType == "Tutti") {
        filteredSensors = sensori;  // Mostra tutti i sensori
    } else {
        for (const auto& sensor : sensori) {
            if (QString::fromStdString(sensor->getInfo()["Tipo"]) == sensorType) {
                filteredSensors.push_back(sensor);
            }
        }
    }

    updateSensorList(filteredSensors);  // Aggiorna la lista con i sensori filtrati
}

void MainWindow::updateSensorList(std::vector<Model::Sensore*>& sensors) {
    if (sensorListWidget) {
        delete sensorListWidget;
        sensorListWidget = nullptr;
    }

    sensorListWidget = new View::SensorListWidget(sensors, this);
    scrollArea->setWidget(sensorListWidget);

    connect(sensorListWidget, &View::SensorListWidget::updateList, this, &MainWindow::dataUpdated);
    connect(sensorListWidget, &View::SensorListWidget::sensorSelected, this, &MainWindow::onSensorSelected);
}
/*
void MainWindow::onSensorModified(std::map<std::string, std::string>& info) {
    //ciclo attraverso il vettore dei sensori per trovare quello selezionato
    qDebug() <<"onsensor trovato";
    for (auto sensore=sensori.begin(); sensore!=sensori.end(); sensore++) {
        if ((*sensore)->getInfo()["ID"] == info["ID"]) {
            qDebug() <<"onsensor trovato";
            //dealloco il vecchio sensore per evitare fughe di memoria
            sensori.erase(sensore);
            qDebug() <<"eliminato";
            //sostituisco il vecchio sensore con il nuovo
            sensori.push_back(creaSensore(mapToJson(info)));
            break;
        }
    }
}*/
void MainWindow::onSensorModified(std::map<std::string, std::string>& info) {
    // Ciclo attraverso il vettore dei sensori per trovare quello selezionato
    qDebug() << "onSensor trovato";
    for (auto sensore = sensori.begin(); sensore != sensori.end(); ++sensore) {
        if ((*sensore)->getInfo()["ID"] == info["ID"]) {
            qDebug() << "onSensor trovato";

            // Creo il nuovo sensore usando i dati passati
            Model::Sensore* newSensor = creaSensore(mapToJson(info));

            // Dealloco il vecchio sensore per evitare fughe di memoria
            delete *sensore;

            // Sostituisco il vecchio sensore con il nuovo nella stessa posizione
            *sensore = newSensor;

            qDebug() << "Sensore sostituito";
            break;
        }
    }
}



