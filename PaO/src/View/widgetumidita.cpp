#include "widgetumidita.h"
#include <QVBoxLayout>
#include <QLabel>

View::WidgetUmidita::WidgetUmidita(Model::Sensore* s,QWidget *parent)
    : WidgetGrafico(this) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Dati del sensore Umidità", this);
    layout->addWidget(label);

    setLayout(layout);
}

void View::WidgetUmidita::updateData(/* data specific to humidity sensor */) {

}
