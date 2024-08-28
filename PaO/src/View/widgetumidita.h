#ifndef WIDGETUMIDITA_H
#define WIDGETUMIDITA_H

#include "widgetgrafico.h"
#include "src/Model/Sensore.h"
#include <QChart>
#include <QChartView>
#include <QTableWidget>
#include <QSplineSeries>

namespace View {

class WidgetUmidita : public WidgetGrafico {
    Q_OBJECT

public:
    explicit WidgetUmidita(Model::Sensore* s, QWidget *parent = nullptr);
    void simulazione(Model::Sensore* sensore);

private:
    QChart *chart;
    QChartView *chartView;
    QTableWidget *tabella;
    QSplineSeries *series;
};

}

#endif
