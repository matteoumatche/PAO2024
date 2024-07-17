#ifndef INFOSENSORE_H
#define INFOSENSORE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QScrollArea>
#include <QLabel>
#include <algorithm>
#include <QMultiMap>

namespace View {
    class infoSensore : public QWidget {
        Q_OBJECT

    private:
        QLabel* type_label;
        QLabel* ID_label;
        QLabel* name_label;
    public:
        infoSensore(QWidget* parent = 0);
        void show();
    };
}