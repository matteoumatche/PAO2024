#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include "../Model/sensore.h"
#include "widgetgrafico.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace View {

class optionsWidget : public QWidget {
    Q_OBJECT

private:
    QHBoxLayout* optionsLayout;             //layout delle opzioni sotto il grafico: contiene i dati, i pulsanti e i pulsanti simula
    QVBoxLayout* dataLayout;                //layout dei dati del sensore
    QVBoxLayout* pulsantiLayout;            //layout dei pulsanti: clona, modifica, elimina
    QVBoxLayout* simulaLayout;              //layout dei pulsanti simula e simula misura
    QWidget* dataWidget;                    //widget che contiene i dati del sensore
    QPushButton* SimulaButton;              //bottone per avviare la simulazione

signals:
    void onCloneClicked(Model::Sensore* s);
    void onModifyClicked(Model::Sensore* s);
    void onDeleteClicked(Model::Sensore* s);
    void onSimulaClicked();

public:
    explicit optionsWidget(Model::Sensore* s, QWidget *parent);
    ~optionsWidget(){};
};

}

#endif
