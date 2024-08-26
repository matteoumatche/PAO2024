#ifndef WIDGETGRAFICO_H
#define WIDGETGRAFICO_H

#include "../Model/sensore.h"

#include <QWidget>

namespace View{

class WidgetGrafico : public QWidget {
    Q_OBJECT

public:
    explicit WidgetGrafico(QWidget *parent = nullptr);

public slots:
    virtual void simulazione(Model::Sensore*);
    virtual void valoreMisura();
};

}

#endif
