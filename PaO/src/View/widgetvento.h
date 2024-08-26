#ifndef WIDGETVENTO_H
#define WIDGETVENTO_H

#include "widgetgrafico.h"
#include "../Model/vento.h"
#include <QPolarChart>
#include <QValueAxis>
#include <QChartView>
#include <QLineSeries>
#include <QTimer>
#include <QTableWidget>



namespace View {
class WidgetVento : public WidgetGrafico {
    Q_OBJECT

public:
    explicit WidgetVento(Model::Sensore* s, QWidget* parent = nullptr);

public slots:
    void simulazione(Model::Sensore* s);

protected:
    void aggiornaGrafico();

private:
    Model::Vento* vento;
    QPolarChart* polarChart;
    QChartView* chartView;
    QLineSeries* series;
    QValueAxis* angularAxis;
    QValueAxis* radialAxis;
    QTimer* timer;
    QTableWidget* tabella;

    int iterazioniRimanenti;
    double angoloCorrente;
};
}

#endif // WIDGETVENTO_H

