#ifndef WIDGETFOTOCELLULA_H
#define WIDGETFOTOCELLULA_H
#include <QWidget>

class WidgetFotocellula : public QWidget {
    Q_OBJECT
public:
    explicit WidgetFotocellula(QWidget *parent = nullptr);
    void updateData(/* data specific to wind sensor */);
};

#endif // WIDGETFOTOCELLULA_H
