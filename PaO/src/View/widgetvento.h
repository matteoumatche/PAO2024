#ifndef WIDGETVENTO_H
#define WIDGETVENTO_H
#include <QWidget>
#include "../Model/vento.h"
#include "widgetgrafico.h"
namespace View{
class WidgetVento : public WidgetGrafico {
    Q_OBJECT
public:
    explicit WidgetVento(Model::Sensore* s, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    void simulazione() override;
    //void misura(double valoreReale);
    //void valoreMisura();

private:
    Model::Vento* vento;
    //std::vector<std::pair<double, double>> datiSimulati; // Per memorizzare i risultati delle 10 simulazioni
    //bool mostraGrafico; // Per determinare quale modalità mostrare (grafico o bussola)
};
}
#endif // WIDGETVENTO_H
