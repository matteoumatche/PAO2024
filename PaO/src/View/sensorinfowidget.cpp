#include "sensorinfowidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QPalette>

View::SensorInfoWidget::SensorInfoWidget(const std::map<std::string, std::string>& info, QWidget* parent)
    : QWidget(parent), sensorID(""){

    QVBoxLayout* layoutDati = new QVBoxLayout(this);

    QVector<QString> keysToDisplay = {"Tipo", "ID", "Nome"};

    for (const auto& pair : info) {
        QString key = QString::fromStdString(pair.first);

        if (key == "ID") {
            sensorID = pair.second;
        }

        if (keysToDisplay.contains(key)) {
            QLabel* label = new QLabel(key + ": " + QString::fromStdString(pair.second), this);
            layoutDati->addWidget(label);
        }
    }

    setLayout(layoutDati);
}

void View::SensorInfoWidget::mousePressEvent(QMouseEvent* event) {
    qDebug() << "passo 1";
    emit sensorSelected(sensorID);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::lightGray); //clore al clic
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    QTimer::singleShot(200, this, [this]() {
        QPalette palette = this->palette();
        palette.setColor(QPalette::Window, QColor(255, 255, 255, 0)); //colore originale
        this->setPalette(palette);
    });

    QWidget::mousePressEvent(event);
}
