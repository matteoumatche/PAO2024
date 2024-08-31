#ifndef WIDGETFOTOCELLULA_H
#define WIDGETFOTOCELLULA_H

#include "widgetgrafico.h"
#include "../Model/Sensore.h"
#include <QTableWidgetItem>
#include <QSplineSeries>
#include <QChart>
#include <QValueAxis>
#include <QChartView>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSplitter>

namespace View{

class WidgetFotocellula : public WidgetGrafico {
    Q_OBJECT
private:
    std::vector<Model::Sensore*>* sensori;
    QSplitter *splitter;
    QChartView *chartView;
    QChart *chart;
    QTableWidget* tabella;
    QSplineSeries *series;

public:
    explicit WidgetFotocellula(std::vector<Model::Sensore*>* s, QWidget *parent = nullptr);
    void simulazione(Model::Sensore*) override;
};

}

#endif
