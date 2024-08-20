#ifndef WIDGETTEMPERATURA_H
#define WIDGETTEMPERATURA_H

#include <QLabel>
#include <QWidget>
#include "../Model/temperatura.h"  // Includi il modello specifico di Temperatura

class WidgetTemperatura : public QWidget {
    Q_OBJECT
public:
    explicit WidgetTemperatura(Model::Temperatura* sensore, QWidget *parent = nullptr);
    void updateData(Model::Temperatura* sensore);  // Ora accetta direttamente un sensore di tipo Temperatura

private:
    QLabel* tempLabel;  // Per mostrare la temperatura
};

#endif // WIDGETTEMPERATURA_H