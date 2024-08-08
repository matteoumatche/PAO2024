#include "toolBar.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QDialogButtonBox>


namespace View {

ToolBar::ToolBar(QToolBar *parent)
    : QToolBar(parent)
{
    newAction = new QAction( tr("Nuovo sensore"), this);
    openAction = new QAction( tr("Apri"), this);
    saveAction = new QAction( tr("Salva"), this);
    saveAsAction = new QAction( tr("Salva con nome"), this);

    // Aggiungi i QAction alla ToolBar
    addAction(newAction);
    addAction(openAction);
    addAction(saveAction);
    addAction(saveAsAction);

    // Collega le shortcut ai QAction
    openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    saveAsAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));

    // Al momento della costruzione non c'è niente da salvare e niente da salvare con nome
    saveAction->setEnabled(false);
    saveAsAction->setEnabled(false);

    connect(newAction, &QAction::triggered, this, &ToolBar::showNewSensorDialog);
    connect(openAction, &QAction::triggered, this, &ToolBar::openSlot);
    connect(saveAction, &QAction::triggered, this, &ToolBar::saveSlot);
    connect(saveAsAction, &QAction::triggered, this, &ToolBar::saveAsSlot);
}

QStringList ToolBar::getAvailableSensorTypes() {
    return QStringList() << "Fotocellula" << "Vento" << "Temperatura" << "Umidità" << "Temperatura percepita";
}

void ToolBar::showNewSensorDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Nuovo Sensore");

    QVBoxLayout *dialogLayout = new QVBoxLayout(&dialog);

    formLayout = new QFormLayout();
    QComboBox *typeComboBox = new QComboBox(&dialog);
    QLineEdit *idEdit = new QLineEdit(&dialog);

    QStringList sensorTypes = getAvailableSensorTypes();
    typeComboBox->addItems(sensorTypes);

    formLayout->addRow("Tipo:", typeComboBox);
    formLayout->addRow("ID:", idEdit);

    dialogLayout->addLayout(formLayout);

    sensorOptionsWidget = new QWidget(&dialog);
    sensorOptionsLayout = new QVBoxLayout(sensorOptionsWidget);
    dialogLayout->addWidget(sensorOptionsWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    dialogLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString type = typeComboBox->currentText();
        QString id = idEdit->text();
        addSensor(type, id);
    }
}

void ToolBar::addSensor(const QString &type, const QString &id) {
    QMessageBox::information(this, "Sensore Aggiunto", "Tipo: " + type + "\nID: " + id);
    // Aggiungi qui il codice per aggiungere il sensore alla tua finestra principale o al tuo sistema
}

void ToolBar::openSlot(){
    emit openSignal();
}

void ToolBar::saveSlot(){
    emit saveSignal();
}

void ToolBar::saveAsSlot(){
    emit saveAsSignal();
}

void ToolBar::activateSaveAction(){
    saveAction->setEnabled(true);
}

void ToolBar::activateSaveAsAction(){
    saveAsAction->setEnabled(true);
}

void ToolBar::disactivateSaveAction(){
    saveAction->setEnabled(false);
    // Non disattivo il "Salva con nome" perchè abilito la possibilità di salvare gli stessi dati in tanti file diversi
    // Se l'utente ha eliminato tutti i sensori, c'è il metodo apposito disactivateSaveAsActionAndButton per disattivare il "Salva con nome"
}

void ToolBar::disactivateSaveAsAction(){
    // Chiamato quando l'utente ha eliminato tutti i sensori, e dunque non c'è niente da salvare con nome
    saveAsAction->setEnabled(false);
}

void ToolBar::openJsonFile()
{
    QString defaultFolder = "src";
    QFileDialog dialog(this);
    dialog.setDirectory(defaultFolder);
    QString fileName = dialog.getOpenFileName(this, "Apri file JSON", defaultFolder,
                                              "JSON Files (*.json);;All Files (*)");

    if (!fileName.isEmpty()) {
        /*
         * delete repository;
        repository = new Sensor::Repository::JsonRepository(Sensor::Repository::JsonRepository::fromPath(fileName.toStdString())); // Static factory method

        * Questa era la precedente implementazione, ma c'era un bug, in certe situazioni non riusciva più a entrare in else, allora sono andato a forza
           bruta eliminando e ricreando ogni volta repository */
        /*if(repository==nullptr)
            repository = new Sensor::Repository::JsonRepository(Sensor::Repository::JsonRepository::fromPath(fileName.toStdString())); // Static factory method
        else{
            repository->setPath(fileName.toStdString());
            qDebug()<<"Sono entrato qui";
        }

        // Load del file Json nel repository, che poi viene salvato nel sensors di MainWindow
        repository->load();
        */
        emit fileOpened();

    }
}

void ToolBar::saveJsonFile(Sensori sensors, std::string nomeFile)
{/*
    if (repository == nullptr) {
        saveJsonFileAs(sensors, repository);
    } else {
        // Sovrascrizione della std::map di repository, che poi archivia nel Json
        repository->overwrite(sensors);
        repository->store();

        emit setIsSaved(true);
    }*/
}

void ToolBar::saveJsonFileAs(Sensori sensors, std::string nomeFile)
{/*
    QString defaultFolder = "JsonDocuments";
    QFileDialog dialog(this);
    dialog.setDirectory(defaultFolder);

    QString fileName = dialog.getSaveFileName(this, "Salva file JSON", defaultFolder, "JSON Files (*.json)");

    if (!fileName.isEmpty()) {
        // Aggiungi l'estensione .json se non è già presente
        if (!fileName.endsWith(".json", Qt::CaseSensitive)) {
            fileName += ".json";
        }

        if(repository==nullptr)
            repository = new Sensor::Repository::JsonRepository(Sensor::Repository::JsonRepository::fromPath(fileName.toStdString())); // Static factory method
        else
            repository->setPath(fileName.toStdString());

        // Sovrascrizione della std::map di repository, che poi archivia nel Json
        repository->overwrite(sensors);
        repository->store();

        emit setIsSaved(true);
    }*/
}

ToolBar::~ToolBar()                // Solo alla chiusura dell'app la ToolBar viene eliminata, non c'è mai una sovrascrizione a runtime,
{                                  // quindi posso mettere i delete solo nel distruttore e non anche all'inizio del costruttore
    delete openAction;
    delete saveAction;
    delete saveAsAction;
}

}
