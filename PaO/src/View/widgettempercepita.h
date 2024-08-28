#ifndef WIDGETTEMPERCEPITA_H
#define WIDGETTEMPERCEPITA_H

#include "widgetgrafico.h"
#include "../Model/Sensore.h"
#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QTableWidget>

namespace View{

class WidgetTempercepita : public WidgetGrafico{
    Q_OBJECT

public:
    explicit WidgetTempercepita(QWidget *parent);

public slots:
    void simulazione(Model::Sensore*) override;

private:
    QBarSet *setTP;
    QBarSet *setTR;
    QBarSeries *series;
    QTableWidget *tabella;
};

}

#endif
/*
#ifndef WIDGETTEMPERCEPITA_H
#define WIDGETTEMPERCEPITA_H

#include "widgetgrafico.h"
#include "../Model/Sensore.h"

namespace View{

class WidgetTempercepita : public WidgetGrafico{

public:
    explicit WidgetTempercepita(Model::Sensore* s, QWidget *parent);

public slots:
    void simulazione(Model::Sensore*) override;
};

}

#endif
*/
