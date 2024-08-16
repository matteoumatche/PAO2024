#ifndef WIDGETUMIDITA_H
#define WIDGETUMIDITA_H
#include <QWidget>

class WidgetUmidita : public QWidget {
    Q_OBJECT
public:
    explicit WidgetUmidita(QWidget *parent = nullptr);
    void updateData(/* data specific to wind sensor */);
};

#endif // WIDGETUMIDITA_H
