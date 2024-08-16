#ifndef WIDGETTEMPERCEPITA_H
#define WIDGETTEMPERCEPITA_H
#include <QWidget>

class WidgetTempercepita : public QWidget {
    Q_OBJECT
public:
    explicit WidgetTempercepita(QWidget *parent = nullptr);
    void updateData(/* data specific to temperature sensor */);
};

#endif // WIDGETTEMPERCEPITA_H
