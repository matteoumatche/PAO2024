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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mainLayout(nullptr), centralLayout(nullptr), centralWidget(nullptr)
{
    setWindowTitle("Greenhouse manager");

    //layout
    mainLayout = new QVBoxLayout;
    centralLayout = new QHBoxLayout;

    //toolbar e widget
    tbar= new View::ToolBar;
    centralWidget = new QWidget(this);
    graphWidget = new QWidget(this);
    sensorListWidget= new SensorListWidget(sensori);


    // Area di scorrimento per la lista dei sensori
    scrollArea = new QScrollArea;

    // Impostazione del widget della lista dei sensori nell'area di scorrimento
    scrollArea->setWidget(sensorListWidget);
    centralLayout->addWidget(scrollArea);

    //impostazioni widget
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    mainLayout->addWidget(tbar);
    mainLayout->addLayout(centralLayout);

    centralLayout->addWidget(scrollArea);
    centralLayout->addWidget(graphWidget);

    //misure
    tbar->setMinimumSize(1024, 30);
    sensorListWidget->setMinimumSize(300, 400);
    centralLayout->setStretchFactor(sensorListWidget, 2);
    centralLayout->setStretchFactor(graphWidget, 2);
    //graphWidget->setFixedSize(500, 400);

/*
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(sensorListWidget);
    centralLayout->addWidget(scrollArea);
*/
    // Connessione dei segnali di ToolBar agli slot di MainWindow
    connect(tbar, &View::ToolBar::newSignal, this, &MainWindow::showNewSensorDialog);
    connect(tbar, &View::ToolBar::openSignal, this, &MainWindow::openJsonFile);
    connect(tbar, &View::ToolBar::saveSignal, this, &MainWindow::saveJsonFile);
    connect(tbar, &View::ToolBar::saveAsSignal, this, &MainWindow::saveJsonFileAs);
    connect(tbar, &View::ToolBar::newSignal, this, &MainWindow::dataUpdated);
    connect(tbar, &View::ToolBar::openSignal, this, &MainWindow::dataUpdated);
    connect(sensorListWidget, &SensorListWidget::sensorCloned, this, &MainWindow::openJsonFile);
    connect(sensorListWidget, &SensorListWidget::reloadRequested, this, &MainWindow::reloadJsonFile);
    connect(sensorListWidget, &SensorListWidget::saveRequested, this, &MainWindow::saveJsonFile);

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
    qWarning() << tipo;
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

QJsonObject MainWindow::mapToJson(const std::map<std::string, std::string>& info) const {
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

void MainWindow::dataUpdated(){

    sensorListWidget= new SensorListWidget(sensori);
    scrollArea->setWidget(sensorListWidget);

}

/*void MainWindow::reloadJsonFile() {
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
    sensorListWidget = new SensorListWidget(sensori, this); // Ricrea il widget
    scrollArea->setWidget(sensorListWidget); // Aggiorna l'area di scorrimento

    tbar->activateSaveAction();  // Abilita il pulsante di salvataggio
    tbar->activateSaveAsAction();
}*/
