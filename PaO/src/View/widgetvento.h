#ifndef WIDGETVENTO_H
#define WIDGETVENTO_H
#include <QWidget>

class WidgetVento : public QWidget {
    Q_OBJECT
public:
    explicit WidgetVento(QWidget *parent = nullptr);
    void updateData(/* data specific to wind sensor */);
};

#endif // WIDGETVENTO_H
