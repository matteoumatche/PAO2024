#include "widgettempercepita.h"

#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSplitter>

View::WidgetTempercepita::WidgetTempercepita(QWidget *parent)
    : WidgetGrafico(parent),
      setTP(new QBarSet("Temperatura percepita")),
      setTR(new QBarSet("Temperatura registrata")),
      series(new QBarSeries()),
      tabella(new QTableWidget(0, 3, this))
{
    // Configura il grafico
    series->append(setTP);
    series->append(setTR);

    QChart *chart = new QChart();
    chart->addSeries(series);

    QStringList categories;
    categories << "9-10" << "10-11" << "11-12" << "12-13" << "13-14" << "14-15" << "15-16" << "16-17" << "17-18" << "18-19";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(-10, 40);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Configura la tabella
    tabella->setHorizontalHeaderLabels(QStringList() << "Orario" << "T. percepita (°C)" << "T. rilevata (°C)");
    tabella->horizontalHeader()->setStretchLastSection(true);
    tabella->verticalHeader()->setVisible(false);

    // Configura lo splitter per disporre graficamente chart e tabella
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(chartView);
    splitter->addWidget(tabella);

    splitter->setSizes(QList<int>() << 2 * 100 << 100);  // 2/3 per il grafico, 1/3 per la tabella

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);
}

void View::WidgetTempercepita::simulazione(Model::Sensore* sensore) {
    // Pulizia dati precedenti
    setTP->remove(0, setTP->count());
    setTR->remove(0, setTR->count());
    tabella->setRowCount(0);

    QStringList categories;
    categories << "9-10" << "10-11" << "11-12" << "12-13" << "13-14" << "14-15" << "15-16" << "16-17" << "17-18" << "18-19";

    for (int i = 0; i < 10; ++i) {
        sensore->simulaMisura();  // Simula una misura
        std::map<std::string, std::string> info = sensore->getInfo();  // Ottiene le informazioni dal sensore
        double percepita = std::stod(info["Indice Calore"]);  // Conversione da stringa a double
        double registrata = std::stod(info["Temperatura"]);
        *setTP << percepita;
        *setTR << registrata;

        int row = tabella->rowCount();
        tabella->insertRow(row);
        tabella->setItem(row, 0, new QTableWidgetItem(categories[i]));  // Imposta l'orario
        tabella->setItem(row, 1, new QTableWidgetItem(QString::number(percepita, 'f', 2)));  // Imposta il valore percepito
        tabella->setItem(row, 2, new QTableWidgetItem(QString::number(registrata, 'f', 2)));  // Imposta il valore registrato
    }
}
