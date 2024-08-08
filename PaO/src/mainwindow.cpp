#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mainLayout(nullptr), centralLayout(nullptr), centralWidget(nullptr), tbar(nullptr)
{
    setWindowTitle("Sensori serra");
    tbar= new View::ToolBar;
    //layout
    mainLayout = new QVBoxLayout;
    centralLayout = new QHBoxLayout;

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

    QComboBox *typeComboBox = new QComboBox(&dialog);
    QLineEdit *idEdit = new QLineEdit(&dialog);

    QStringList sensorTypes = getAvailableSensorTypes();
    typeComboBox->addItems(sensorTypes);

    formLayout->addRow("Tipo:", typeComboBox);
    formLayout->addRow("ID:", idEdit);

    dialogLayout->addLayout(formLayout);


    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    dialogLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    dialog.show();
    if (dialog.exec() == QDialog::Accepted) {
        QString type = typeComboBox->currentText();
        QString id = idEdit->text();
        addSensor(type, id);
    }


}

void MainWindow::addSensor(const QString &type, const QString &id){
    QMessageBox::information(this, "Sensore Aggiunto", "Tipo: " + type + "\nID: " + id);
    // Aggiungi qui il codice per aggiungere il sensore alla tua finestra principale o al tuo sistema
}

QStringList MainWindow::getAvailableSensorTypes() {
    return QStringList() << "Fotocellula" << "Vento" << "Temperatura" << "Umidità" << "Temperatura percepita";
}
