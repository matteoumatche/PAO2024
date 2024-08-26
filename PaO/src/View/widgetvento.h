#ifndef WIDGETVENTO_H
#define WIDGETVENTO_H

#include "widgetgrafico.h"
#include "../Model/vento.h"
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QMap>
#include <QPair>
#include <QDateTime>

//QT_CHARTS_USE_NAMESPACE

    namespace View {

    class WidgetVento : public WidgetGrafico {
        Q_OBJECT

    public:
        WidgetVento(Model::Sensore* s, QWidget* parent = nullptr);

    public slots:
        void simulazione(Model::Sensore* s) override;

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        Model::Vento* vento;
        QChart* chart;
        QChartView* chartView;
        QLineSeries* series;
        QMap<QDateTime, QPair<double, double>> datiSimulati;
        bool mostraGrafico;
    };

} // namespace View

#endif // WIDGETVENTO_H

