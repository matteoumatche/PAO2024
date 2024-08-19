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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mainLayout(nullptr), centralLayout(nullptr), centralWidget(nullptr),sensorListWidget(nullptr)
{
    setWindowTitle("Greenhouse manager");

    connect(sensorListWidget, &View::SensorListWidget::updateList, this, &MainWindow::dataUpdated);

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
    centralWidget = new QWidget(this);
    tbar= new View::ToolBar;
    sensorListWidget= new View::SensorListWidget(sensori,this);
    graphWidget = new QWidget(this);
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("Cerca sensori per nome...");
    searchButton = new QPushButton("Cerca", this);
    dataWidget = new QWidget(this);

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
    centralLayout->addWidget(graphWidget);

    //sensorWidgetLayout
    sensorWidgetLayout->addWidget(scrollArea);
    sensorWidgetLayout->addLayout(searchLayout);

    //searchLayout
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    //optionsLayout
    optionsLayout->addWidget(dataWidget);
    optionsLayout->addLayout(pulsantiLayout);
    optionsLayout->addLayout(simulaLayout);

    //---------------------------------------------------

    //misure
    tbar->setMinimumSize(1024, 30);
    sensorListWidget->setMinimumSize(300, 400);
    centralLayout->setStretchFactor(sensorListWidget, 2);
    centralLayout->setStretchFactor(graphWidget, 2);

    // Connessione dei segnali di ToolBar agli slot di MainWindow
    connect(tbar, &View::ToolBar::newSignal, this, &MainWindow::showNewSensorDialog);
    connect(tbar, &View::ToolBar::openSignal, this, &MainWindow::openJsonFile);
    connect(tbar, &View::ToolBar::saveSignal, this, &MainWindow::saveJsonFile);
    connect(tbar, &View::ToolBar::saveAsSignal, this, &MainWindow::saveJsonFileAs);
    connect(tbar, &View::ToolBar::newSignal, this, &MainWindow::dataUpdated);
    connect(tbar, &View::ToolBar::openSignal, this, &MainWindow::dataUpdated);
    connect(sensorListWidget, &View::SensorListWidget::updateList, this, &MainWindow::dataUpdated);
    connect(sensorListWidget, &View::SensorListWidget::sensorSelected, this, &MainWindow::onSensorSelected);

    qDebug() << "Configuro la connessione del segnale sensorSelected";
/*
    connect(sensorListWidget, &View::SensorListWidget::sensorSelected, this, [this](const std::map<std::string, std::string>& sensorInfo) {
        qDebug() << "Segnale sensorSelected ricevuto in MainWindow";
        onSensorSelected(sensorInfo); // Chiama il metodo slot
    });*/
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

Model::Sensore* MainWindow::creaSensore(const QJsonObject& info) const {
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

void MainWindow::onSensorSelected(Model::Sensore* s) {
    qDebug() << "onSensorSelected chiamato";

    if (!s) {
        qDebug() << "Errore: sensore nullo";
        return;
    }

    // Prima di creare un nuovo widget, eliminiamo il vecchio
    if (dataWidget) {
        qDebug() << "1";
        delete dataWidget;
        dataWidget = nullptr;
    }

    qDebug() << "2";
    // Creiamo un nuovo widget per visualizzare i dettagli del sensore
    dataWidget = new QWidget(this);
    qDebug() << "3";
    QVBoxLayout* dataLayout = new QVBoxLayout(dataWidget);
    qDebug() << "4";
    // Recuperiamo le informazioni del sensore
    std::map<std::string, std::string> info = s->getInfo();
    if (info.empty()) {
        qDebug() << "Errore: informazioni del sensore vuote";
        return;
    }
    qDebug() << "5";
    // Visualizziamo solo le chiavi tranne "Tipo", "ID" e "Nome"
        for (const auto& pair : info) {
            qDebug() << "6";
            QString key = QString::fromStdString(pair.first);
            if (key != "Tipo" && key != "ID" && key != "Nome") {
                QLabel* label = new QLabel(key + ": " + QString::fromStdString(pair.second), dataWidget);
                dataLayout->addWidget(label);
            }
        }

        // Imposta il layout del nuovo widget e aggiungilo a optionsLayout
        dataWidget->setLayout(dataLayout);
        optionsLayout->addWidget(dataWidget);
}
