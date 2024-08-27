#include "../View/optionsWidget.h"
#include "widgetgrafico.h"
#include "widgetfotocellula.h"
#include "widgettemperatura.h"
#include "widgettempercepita.h"
#include "widgetumidita.h"
#include "widgetvento.h"
#include "../mainwindow.h"

#include <QLabel>

View::optionsWidget::optionsWidget(Model::Sensore* s, QWidget *parent) :
    QWidget(parent), optionsLayout(nullptr), dataLayout(nullptr), pulsantiLayout(nullptr),
    simulaLayout(nullptr), dataWidget(nullptr), SimulaButton(nullptr) {

    optionsLayout = new QHBoxLayout(this);

    dataWidget = new QWidget(this);
    dataLayout = new QVBoxLayout;

    pulsantiLayout = new QVBoxLayout;

    simulaLayout = new QVBoxLayout;
    SimulaButton = new QPushButton("Simula misure", this);

    std::map<std::string, std::string> info = s->getInfo();
    for (const auto& pair : info) {
        QString key = QString::fromStdString(pair.first);
        if (key != "Tipo" && key != "ID" && key != "Nome") {
            QLabel* label = new QLabel(key + ": " + QString::fromStdString(pair.second), dataWidget);
            dataLayout->addWidget(label);
        }
    }

    //pulsanti "Clona", "Modifica", "Elimina"
    QPushButton *cloneButton = new QPushButton("Clona", this);
    QPushButton *modifyButton = new QPushButton("Modifica", this);
    QPushButton *deleteButton = new QPushButton("Elimina", this);

    connect(cloneButton, &QPushButton::clicked, this, [this, s]() {
        emit onCloneClicked(s);
    });

    connect(modifyButton, &QPushButton::clicked, this, [this, s]() {
        emit onModifyClicked(s);
    });

    connect(deleteButton, &QPushButton::clicked, this, [this, s]() {
        emit onDeleteClicked(s);
    });

    connect(SimulaButton, &QPushButton::clicked, this, [this, s]() {
        emit onSimulaClicked();
    });

    optionsLayout->addWidget(dataWidget);
    optionsLayout->addLayout(pulsantiLayout);
    optionsLayout->addLayout(simulaLayout);

    dataWidget->setLayout(dataLayout);

    pulsantiLayout->addWidget(cloneButton);
    pulsantiLayout->addWidget(modifyButton);
    pulsantiLayout->addWidget(deleteButton);

    simulaLayout->addWidget(SimulaButton);

}


