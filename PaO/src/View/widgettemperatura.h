#ifndef WIDGETTEMPERATURA_H
#define WIDGETTEMPERATURA_H

#include "../Model/temperatura.h"
#include "widgetgrafico.h"

#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QChartView>
#include <QTableWidget>

namespace View {

class WidgetTemperatura : public WidgetGrafico {
    Q_OBJECT

public slots:
    void simulazione(Model::Sensore* sensore) override;

public:
    explicit WidgetTemperatura(Model::Sensore* sensore, QWidget *parent = nullptr);

private:
    QBarSet* set;                  // Puntatore al QBarSet per la temperatura
    QBarSeries* series;            // Puntatore alla serie di barre del grafico
    QChart* chart;                 // Puntatore al grafico
    QChartView* chartView;         // Puntatore alla vista del grafico
    QTableWidget* tabella;         // Puntatore alla tabella dei dati
};

} // namespace View

#endif

/*
#ifndef WIDGETTEMPERATURA_H
#define WIDGETTEMPERATURA_H

#include "../Model/temperatura.h"
#include "widgetgrafico.h"

#include <QLabel>
#include <QBarSeries>

namespace View{

class WidgetTemperatura : public WidgetGrafico {
    Q_OBJECT
public slots:
    void simulazione(Model::Sensore* sensore) override;
public:
    explicit WidgetTemperatura(Model::Sensore* sensore, QWidget *parent = nullptr);
    void updateData(Model::Temperatura* sensore);
    QBarSeries graficoTemperatura;

private:
    QLabel* tempLabel;
};

}

#endif
*/
