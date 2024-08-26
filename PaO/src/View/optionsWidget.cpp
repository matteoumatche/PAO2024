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

    optionsLayout = new QHBoxLayout;
    dataLayout = new QVBoxLayout;
    pulsantiLayout = new QVBoxLayout;
    simulaLayout = new QVBoxLayout;
    dataWidget = new QWidget;
    SimulaButton = new QPushButton("Simula misure", this);

    dataWidget = new QWidget(this);
    QVBoxLayout* dataLayout = new QVBoxLayout(dataWidget);
    qDebug() << "ciao";

    std::map<std::string, std::string> info = s->getInfo();
    for (const auto& pair : info) {
        QString key = QString::fromStdString(pair.first);
        if (key != "Tipo" && key != "ID" && key != "Nome") {
            QLabel* label = new QLabel(key + ": " + QString::fromStdString(pair.second), dataWidget);
            dataLayout->addWidget(label);
        }
    }
    qDebug() << "ciao";

    optionsLayout->addWidget(dataWidget);
/*
    if (SimulaButton) {
        //CRASH durante l'esecuzione del delete
        delete SimulaButton;
        SimulaButton = nullptr;
    }*/

    //SimulaButton = new QPushButton("Simula misure", this);
    qDebug() << "ciao1";

    simulaLayout->addWidget(SimulaButton);
    qDebug() << "ciao2";

    emit onSimulaClicked();

    dataWidget->setLayout(dataLayout);

    //pulsanti "Clona", "Modifica", "Elimina"
    QPushButton *cloneButton = new QPushButton("Clona", this);
    QPushButton *modifyButton = new QPushButton("Modifica", this);
    QPushButton *deleteButton = new QPushButton("Elimina", this);

    pulsantiLayout->addWidget(cloneButton);
    pulsantiLayout->addWidget(modifyButton);
    pulsantiLayout->addWidget(deleteButton);

    connect(cloneButton, &QPushButton::clicked, this, [this, s]() {
        emit onCloneClicked(s);
    });

    connect(modifyButton, &QPushButton::clicked, this, [this, s]() {
        emit onModifyClicked(s);
    });

    connect(deleteButton, &QPushButton::clicked, this, [this, s]() {
        emit onDeleteClicked(s);
    });

    optionsLayout->addLayout(pulsantiLayout);
    optionsLayout->addLayout(simulaLayout);

}

/*
    if (dataWidget) {
        delete dataWidget;
        dataWidget = nullptr;
    }
    */

/*
    if (pulsantiLayout) {
        QLayoutItem *item;
        while ((item = pulsantiLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }*/

