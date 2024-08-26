#include "widgetfotocellula.h"
#include <QVBoxLayout>
#include <QLabel>

View::WidgetFotocellula::WidgetFotocellula(Model::Sensore* s,QWidget *parent)
    : WidgetGrafico(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    //etichetta generica
    QLabel* label = new QLabel("Dati del sensore Fotocellula", this);
    layout->addWidget(label);

    setLayout(layout);
}

void View::WidgetFotocellula::updateData(/* data specific to wind sensor */) {

}
