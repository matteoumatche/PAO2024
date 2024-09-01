#include "sensorlistwidget.h"
#include "sensorinfowidget.h"
#include "../Model/fotocellula.h"

#include <QLayout>
#include <QFrame>

View::SensorListWidget::SensorListWidget(std::vector<Model::Sensore*>& sensori, QWidget* parent)
    : QWidget(parent), sensori(sensori) {

    QVBoxLayout* layout = new QVBoxLayout();

    //ordinazione Fotocellule alla fine
    std::sort(this->sensori.begin(), this->sensori.end(), [](Model::Sensore* a, Model::Sensore* b) {
        auto isFotocellulaA = dynamic_cast<Model::Fotocellula*>(a) != nullptr;
        auto isFotocellulaB = dynamic_cast<Model::Fotocellula*>(b) != nullptr;
        return isFotocellulaA < isFotocellulaB;
    });

    bool addedDivider = false;

    for (Model::Sensore* sensore : sensori) {
        std::map<std::string, std::string> info = sensore->getInfo();
        SensorInfoWidget* sensorWidget = new SensorInfoWidget(info, this);

        QHBoxLayout* layoutInterno = new QHBoxLayout();
        layoutInterno->addWidget(sensorWidget);

        QVBoxLayout* layoutBottoni = new QVBoxLayout();

        connect(sensorWidget, &SensorInfoWidget::sensorSelected,this, &SensorListWidget::onSensorSelected);

        layoutInterno->addLayout(layoutBottoni);

        //divisore prima dei Fotocellula
        if (!addedDivider && dynamic_cast<Model::Fotocellula*>(sensore)) {
            QFrame* line = new QFrame();
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            layout->addWidget(line);
            addedDivider = true; //impedisce di aggiungere più di un divisore
        }

        layout->addLayout(layoutInterno);
    }

    setLayout(layout);
}

void View::SensorListWidget::onSensorSelected(const std::string& sensorID){
    emit sensorSelected(sensorID);
}

