#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include "src/Model/sensore.h"
#include "src/Model/fotocellula.h"
#include "src/Model/temperatura.h"
#include "src/Model/tempercepita.h"
#include "src/Model/umidita.h"
#include "src/Model/vento.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mainLayout(nullptr), centralLayout(nullptr), centralWidget(nullptr), tbar(nullptr)
{
    setWindowTitle("Sensori serra");

    //layout
    mainLayout = new QVBoxLayout;
    centralLayout = new QHBoxLayout;

    //toolbar
    tbar= new View::ToolBar;

    //pannello principale
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    tbar->setFixedSize(1024, 30);



    mainLayout->addWidget(tbar);
    // Connessione del segnale di ToolBar allo slot di MainWindow
    connect(tbar, &View::ToolBar::newSignal, this, &MainWindow::showNewSensorDialog);

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

    formLayout->addRow("Nome:", nameEdit);
    formLayout->addRow("Tipo:", typeComboBox);
    formLayout->addRow("ID:", idEdit);

    dialogLayout->addLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    dialogLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    dialog.show();
    if (dialog.exec() == QDialog::Accepted) {
        QString name = nameEdit->text();
        QString type = typeComboBox->currentText();
        QString id = idEdit->text();
        addSensor(name, type, id);
    }
}

void MainWindow::addSensor(const QString &name, const QString &type, const QString &id){
    Model::Sensore* nuovoSensore = nullptr;

    if (type == "Fotocellula") {
        nuovoSensore = new Model::Fotocellula(id, name, 0, 0);  // Sostituisci con la tua classe specifica
    } else if (type == "Tipo2") {
        nuovoSensore = new Model::Tipo2Sensore(id);  // Sostituisci con la tua classe specifica
    } else if (type == "Tipo3") {
        nuovoSensore = new Model::Tipo3Sensore(id);  // Sostituisci con la tua classe specifica
    }

    if (nuovoSensore) {
        sensori.push_back(nuovoSensore);
    }

    QMessageBox::information(this, "Sensore Aggiunto", "Tipo: " + type + "\nID: " + id);
}

QStringList MainWindow::getAvailableSensorTypes() {
    return QStringList() << "Fotocellula" << "Vento" << "Temperatura" << "Umidità" << "Temperatura percepita";
}
