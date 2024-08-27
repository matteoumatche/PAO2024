#include "widgetfotocellula.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSplineSeries>
#include <QChart>
#include <QValueAxis>
#include <QChartView>

View::WidgetFotocellula::WidgetFotocellula(std::vector<Model::Sensore*>* s ,QWidget *parent)
    : WidgetGrafico(parent), sensori(s){

}
void View::WidgetFotocellula::simulazione(Model::Sensore* s) {
    qDebug()<<"sim foto";
    /*if (layout()) {
        qDebug()<<"sim foto 1";
        QLayoutItem* item;
        while ((item = layout()->takeAt(0)) != nullptr) {
            qDebug()<<"sim foto 3";
            delete item->widget();  // Rimuove i widget figli
            delete item;  // Rimuove il layout item
        }
        //delete oldLayout;
    }*/
    qDebug()<<"sim foto 4";
    QSplineSeries *series = new QSplineSeries();
    series->setName("visitatori");
    int j=0;
    //oggetto ora = apertura
    for(int i=0;i<50;i++){
        //ora= ora+ i*0.2*(orachiusura-oraapertura)
        qDebug()<<"sim foto i:"<< i;

        for (std::vector<Model::Sensore*>::iterator it=sensori->begin();it!=sensori->end();it++) {
            if((*it)->getInfo()["Tipo"]=="Fotocellula"){
                qDebug()<<"sim foto j:"<< j;
                (*it)->simulaMisura();  //simula una misura
                qDebug()<<"sim foto simula j:"<< j;
                (*it)->getInfo()["Attivo"]!="false"?j++:j--;
            }
        }
        qDebug()<<"series";
        series->append(/*ora*/i,j);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("andamento numero visitatori");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, j+(0.2*j));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}
