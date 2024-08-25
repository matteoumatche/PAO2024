#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
#include <QScrollArea>
#include <QMessageBox>
#include <QDebug>
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mainLayout(nullptr), centralLayout(nullptr), centralWidget(nullptr),sensorListWidget(nullptr)
{
    setWindowTitle("Greenhouse manager");

    //layout
    mainLayout = new QVBoxLayout;           //layout principale: contiene Toolbar e centalLayout
    centralLayout = new QHBoxLayout;        //layout sotto Toolbar: contiene sensorWidgetLayout e graphWidget
    sensorWidgetLayout = new QVBoxLayout;   //layout della lista: contiene sensorListWidget e searchLayout
    searchLayout = new QHBoxLayout;         //layout della barra di ricerca: contiene barra e bottone
    graphLayout = new QVBoxLayout;          //layout della zona a destra della lista: contiene graphWidget e optionsLayout
    optionsLayout = new QHBoxLayout;        //layout delle opzioni sotto il grafico: contiene i dati, i pulsanti e i pulsanti simula
    pulsantiLayout = new QVBoxLayout;       //layout dei pulsanti: clona, modifica, elimina
    simulaLayout = new QVBoxLayout;         //layout dei pulsanti simula e simula misura

    //toolbar e widget
    centralWidget = new QWidget(nullptr);
    tbar= new View::ToolBar;
    sensorListWidget= new View::SensorListWidget(sensori,nullptr);
    graphWidget = new View::WidgetGrafico(nullptr);
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("Cerca sensori per nome...");
    //searchButton = new QPushButton("Cerca", this);
    dataWidget = new QWidget(nullptr);

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

    //graphLayout
    //graphLayout->addWidget(graphWidget);
    graphLayout->addLayout(optionsLayout);

    //searchLayout
    searchLayout->addWidget(searchLineEdit);
    //searchLayout->addWidget(searchButton);

    //optionsLayout
    //optionsLayout->addWidget(dataWidget);
    optionsLayout->addLayout(pulsantiLayout);
    optionsLayout->addLayout(simulaLayout);

    //---------------------------------------------------

    //misure
    tbar->setMinimumSize(1024, 30);
    sensorListWidget->setMinimumSize(300, 400);
    centralLayout->setStretchFactor(sensorListWidget, 2);
    centralLayout->setStretchFactor(graphLayout, 2);
    dataWidget->adjustSize();
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

    QPushButton* clearSearchButton;
    searchButton = new QPushButton("Cerca", nullptr);
    clearSearchButton = new QPushButton("Annulla ricerca", nullptr);
    searchLayout->addWidget(searchButton);
    searchLayout->addWidget(clearSearchButton);

    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);
    connect(clearSearchButton, &QPushButton::clicked, this, &MainWindow::onClearSearchButtonClicked);
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

    connect(buttonBox, &QDialogButtonBox::accepted, [this, &dialog, typeComboBox, idEdit, nameEdit]() { // Cattura per riferimento
        QString type = typeComboBox->currentText();
        QString id = idEdit->text();
        QString name = nameEdit->text();

        if (id.isEmpty() || name.isEmpty()) {
            QMessageBox::warning(&dialog, "Errore", "I campi 'ID' e 'Nome' devono essere riempiti.");
            return; // Non chiudere il dialogo
        }

        // Validazione dell'ID
        QRegularExpression idRegex("^[0-9]{4}$");
        if (!idRegex.match(id).hasMatch()) {
            QMessageBox::warning(&dialog, "Errore", "L'ID deve avere esattamente 4 caratteri numerici.");
            return; // Non chiudere il dialogo
        }

        // Validazione del Nome
        QRegularExpression nameRegex("^[A-Za-z0-9]+$"); // Nome deve essere composto solo da caratteri alfabetici
        if (!nameRegex.match(name).hasMatch()) {
            QMessageBox::warning(&dialog, "Errore", "Il Nome deve contenere solo caratteri alfanumerici.");
            return; // Non chiudere il dialogo
        }

        addSensor(type, id, name);
        dialog.accept(); // Chiudere il dialogo se tutti i controlli sono superati
    });

    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    dialog.exec();
}

void MainWindow::addSensor(const QString &type, const QString &id, const QString &name){
    // Controllo se l'ID o il nome sono già esistenti
    for (const auto& sensore : sensori) {
        if (sensore->getID() == id.toUInt() || sensore->getNome() == name.toStdString()) {
            QMessageBox::warning(this, "Errore", "ID o Nome già esistenti. Inserire valori unici.");
            return; // Non aggiungere il sensore se l'ID o il nome esistono già
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
    } else if (type == "TemPercepita") {
        nuovoSensore = new Model::TemPercepita(id.toUInt(), name.toStdString());
    }

    if (nuovoSensore) {
        sensori.push_back(nuovoSensore);
    }

    QMessageBox::information(this, "Sensore Aggiunto", "Tipo: " + type + "\nID: " + id + "\nNome: " + name);
    tbar->activateSaveAction();  // Abilita il pulsante di salvataggio
    tbar->activateSaveAsAction();

}

QStringList MainWindow::getAvailableSensorTypes() {
    return QStringList() << "Fotocellula" << "Vento" << "Temperatura" << "Umidità" << "TemPercepita";
}

Model::Sensore* MainWindow::creaSensore(const QJsonObject& info)  {
    QString tipo = info["Tipo"].toString();
   // qWarning() << tipo;
    if (!tipo.isEmpty()) {
        if (tipo == "Fotocellula") {
            return new Model::Fotocellula(info);
        } else if (tipo == "Temperatura") {
            return new Model::Temperatura(info);
        }else if (tipo == "Vento") {
            return new Model::Vento(info);
        }else if (tipo == "Umidita") {
            return new Model::Umidita(info);
        }else if (tipo == "TemPercepita") {
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

    // Pulizia dei sensori esistenti
    sensori.clear();

    for (const QJsonValue& i : arraySensori) {
        QJsonObject sen_obj = i.toObject();

        // Usa la funzione  per creare il sensore corretto
        Model::Sensore* sensore = creaSensore(sen_obj);
        if (sensore) {
            sensori.push_back(sensore);
        } else {
            qWarning() << "Tipo di sensore non riconosciuto o errore nella creazione.";
        }
    }

    pathToFile = nomeFile;
    tbar->activateSaveAction();  // Abilita il pulsante di salvataggio
    tbar->activateSaveAsAction();
}

void MainWindow::saveJsonFile(){
    if (pathToFile.isEmpty()) {
        saveJsonFileAs();  // Se non c'è un file aperto, richiama saveJsonFileAs()
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

    // Aggiungi l'estensione .json se non è presente
    if (!fileName.endsWith(".json", Qt::CaseInsensitive)) {
        fileName += ".json";
    }

    pathToFile = fileName;
    saveJsonFile();
}

void MainWindow::dataUpdated() {
    qDebug() << "dataUpdated";

    // Prima di creare un nuovo widget, eliminiamo il vecchio
    if (sensorListWidget) {
        delete sensorListWidget;
        sensorListWidget = nullptr;
    }

    // Ricrea il widget con la lista aggiornata
    sensorListWidget = new View::SensorListWidget(sensori, this);
    scrollArea->setWidget(sensorListWidget);

    // Riconnetti i segnali
    connect(sensorListWidget, &View::SensorListWidget::updateList, this, &MainWindow::dataUpdated);
    connect(sensorListWidget, &View::SensorListWidget::sensorSelected, this, &MainWindow::onSensorSelected);
}

void MainWindow::reloadJsonFile() {
    if (pathToFile.isEmpty()) {
        return; // Non c'è un file da ricaricare
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

    // Pulizia dei sensori esistenti
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

    // Ricarica la lista dei sensori
    sensorListWidget = new View::SensorListWidget(sensori, this); // Ricrea il widget
    scrollArea->setWidget(sensorListWidget); // Aggiorna l'area di scorrimento

    tbar->activateSaveAction();  // Abilita il pulsante di salvataggio
    tbar->activateSaveAsAction();
}
void MainWindow::onSensorSelected(const std::string sensorID) {

    // Trova il sensore selezionato
    Model::Sensore* selectedSensor = nullptr;
    for (Model::Sensore* sensore : sensori) {
        if (std::to_string(sensore->getID()) == sensorID) {
            selectedSensor = sensore;
            break;
        }
    }

    // Se il sensore non è trovato, pulisci tutto e ritorna
    if (!selectedSensor) {
        // Pulisce il layout dei pulsanti
        if (pulsantiLayout) {
            QLayoutItem *item;
            while ((item = pulsantiLayout->takeAt(0)) != nullptr) {
                delete item->widget(); // Elimina i widget contenuti
                delete item; // Elimina il layout item
            }
        }

        // Pulisce il layout della simulazione
        if (simulaLayout) {
            QLayoutItem *item;
            while ((item = simulaLayout->takeAt(0)) != nullptr) {
                delete item->widget(); // Elimina i widget contenuti
                delete item; // Elimina il layout item
            }
        }

        // Pulisce il widget dei dati
        if (dataWidget) {
            delete dataWidget;
            dataWidget = nullptr;
        }

        // Pulisce il widget grafico
        if (graphWidget) {
            delete graphWidget;
            graphWidget = nullptr;
        }

        return; // Termina la funzione se il sensore non è trovato
    }

    // Se il sensore è trovato, aggiorna i widget
    if (dataWidget) {
        delete dataWidget;
        dataWidget = nullptr;
    }

    if (graphWidget) {
        delete graphWidget;
        graphWidget = nullptr;
    }

    // Pulisce il layout dei pulsanti
    if (pulsantiLayout) {
        QLayoutItem *item;
        while ((item = pulsantiLayout->takeAt(0)) != nullptr) {
            delete item->widget(); // Elimina i widget contenuti
            delete item; // Elimina il layout item
        }
    }

    // Crea e imposta un nuovo widget per i dati del sensore
    dataWidget = new QWidget(this); // Imposta il parent
    QVBoxLayout* dataLayout = new QVBoxLayout(dataWidget); // Imposta il layout

    // Recupera e mostra le informazioni del sensore
    std::map<std::string, std::string> info = selectedSensor->getInfo();
    for (const auto& pair : info) {
        QString key = QString::fromStdString(pair.first);
        if (key != "Tipo" && key != "ID" && key != "Nome") {
            QLabel* label = new QLabel(key + ": " + QString::fromStdString(pair.second), dataWidget);
            dataLayout->addWidget(label);
        }
    }

    optionsLayout->addWidget(dataWidget);

    // Gestione del pulsante di simulazione
    if (SimulaButton) {
        delete SimulaButton;
        SimulaButton = nullptr;
    }
    SimulaButton = new QPushButton("Simula misure", this); // Imposta il parent
    simulaLayout->addWidget(SimulaButton);

    // Crea e gestisce il widget grafico
    if (graphWidget) {
        delete graphWidget;
        graphWidget = nullptr;
    }

    if (info["Tipo"] == "Vento") {
        graphWidget = new View::WidgetVento(selectedSensor, this);
    } else if (info["Tipo"] == "Temperatura") {
        graphWidget = new View::WidgetTemperatura(selectedSensor, this);
    } else if (info["Tipo"] == "Umidita") {
        graphWidget = new View::WidgetUmidita(selectedSensor, this);
    } else if (info["Tipo"] == "TemPercepita") {
        graphWidget = new View::WidgetTempercepita(selectedSensor, this);
    } else if (info["Tipo"] == "Fotocellula") {
        graphWidget = new View::WidgetFotocellula(selectedSensor, this);
    } else {
        graphWidget = new View::WidgetGrafico(this); // Corretto
    }

    connect(SimulaButton, &QPushButton::clicked, graphWidget, &View::WidgetGrafico::simulazione);

    graphLayout->addWidget(graphWidget);

    // Imposta il layout del widget dei dati
    dataWidget->setLayout(dataLayout);

    // Creazione e gestione dei pulsanti "Clona", "Modifica", "Elimina"
    QPushButton *cloneButton = new QPushButton("Clona", this);
    QPushButton *modifyButton = new QPushButton("Modifica", this);
    QPushButton *deleteButton = new QPushButton("Elimina", this);

    pulsantiLayout->addWidget(cloneButton);
    pulsantiLayout->addWidget(modifyButton);
    pulsantiLayout->addWidget(deleteButton);

    connect(cloneButton, &QPushButton::clicked, this, [this, selectedSensor]() {
        cloneSensor(selectedSensor);
    });

    connect(modifyButton, &QPushButton::clicked, this, [this, selectedSensor]() {
        modifySensor(selectedSensor);
    });

    connect(deleteButton, &QPushButton::clicked, this, [this, selectedSensor]() {
        deleteSensor(selectedSensor);
    });
}



void MainWindow::cloneSensor(Model::Sensore* selectedSensor){
    if (selectedSensor) {
        // Clona il sensore selezionato
        Model::Sensore* clonedSensor = selectedSensor->clone();

        // Aggiungi il sensore clonato alla lista dei sensori
        sensori.push_back(clonedSensor);

        // Aggiorna la visualizzazione
        emit sensorListWidget->updateList();
    }
}

void MainWindow::modifySensor(Model::Sensore* selectedSensor) {
    if (selectedSensor) {
        // Crea il dialogo di modifica
        EditSensorDialog* dialog = new EditSensorDialog(selectedSensor, this);

        // Connetti il segnale sensorModified allo slot onSensorModified
        connect(dialog, &EditSensorDialog::sensorModified, this, &MainWindow::onSensorModified);

        // Esegui il dialogo e attendi l'input dell'utente
        if (dialog->exec() == QDialog::Accepted) {
            qDebug() <<"accettato";
            // Se l'utente ha accettato le modifiche, aggiorna la visualizzazione della lista dei sensori
            emit sensorListWidget->updateList();
            onSensorSelected(selectedSensor->getInfo()["ID"]);
        }

        // Disconnetti il segnale per evitare connessioni multiple (opzionale, utile se la finestra viene ricreata)
        disconnect(dialog, &EditSensorDialog::sensorModified, this, &MainWindow::onSensorModified);
    }
}

void MainWindow::deleteSensor(Model::Sensore* selectedSensor){
    if (selectedSensor) {
        // Trova ed elimina il sensore selezionato
        auto it = std::find_if(sensori.begin(), sensori.end(),
                               [&selectedSensor](Model::Sensore* sensore) {
                                   return sensore->getID() == selectedSensor->getID();
                               });
        if (it != sensori.end()) {
            delete *it;  // Dealloca la memoria del sensore
            sensori.erase(it);  // Rimuovi il sensore dal vettore
            selectedSensor = nullptr;  // Resetta il sensore selezionato
        }

        // Aggiorna la visualizzazione
        emit sensorListWidget->updateList();
        onSensorSelected("eliminato");
    }
}

void MainWindow::onSearchButtonClicked() {
    QString searchText = searchLineEdit->text();
    std::vector<Model::Sensore*> filteredSensors;

    for (const auto& sensor : sensori) {
        if (QString::fromStdString(sensor->getNome()).contains(searchText, Qt::CaseInsensitive)) {
            filteredSensors.push_back(sensor);  // Usa push_back per aggiungere gli elementi
        }
    }

    updateSensorList(filteredSensors);
}

void MainWindow::onClearSearchButtonClicked() {
    searchLineEdit->clear();
    updateSensorList(sensori); // Ripristina la lista originale
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

void MainWindow::onSensorModified(std::map<std::string, std::string>& info) {
    // Cicla attraverso il vettore dei sensori per trovare quello selezionato
    qDebug() <<"onsensor trovato";
    for (auto sensore=sensori.begin();sensore!=sensori.end();sensore++) {
        if ((*sensore)->getInfo()["ID"] == info["ID"]) {
            qDebug() <<"onsensor trovato";
            // Dealloca il vecchio oggetto sensore per evitare fughe di memoria
            sensori.erase(sensore);
            qDebug() <<"eliminato";
            // Sostituisci il vecchio sensore con il nuovo
            sensori.push_back(creaSensore(mapToJson(info)));
            break;
        }
    }
}




