#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/View/toolbar.h"
#include "View/sensorlistwidget.h"
#include "View/sensorinfowidget.h"
#include "View/widgetgrafico.h"
#include "View/optionsWidget.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QComboBox>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* centralLayout;
    QHBoxLayout* searchLayout;
    QVBoxLayout* graphLayout;
    QWidget* centralWidget;
    View::ToolBar* tbar;
    View::SensorListWidget* sensorListWidget;
    View::SensorInfoWidget* sensorInfoWidget;
    QVBoxLayout* sensorWidgetLayout;
    QScrollArea* scrollArea;
    QLineEdit *searchLineEdit;
    QComboBox* filterComboBox;
    //QPushButton *MisuraButton;
    View::optionsWidget* opzioni;
    View::WidgetGrafico* graphWidget;
    QLabel* titoloLabel;

    std::vector<Model::Sensore*> sensori;
    QString pathToFile;

    QStringList getAvailableSensorTypes();
    void updateSensorList(std::vector<Model::Sensore*>&);

private slots:

    void addSensor(const QString &name, const QString &type, const QString &id);
    void showNewSensorDialog();

    void openJsonFile();
    void saveJsonFile();
    void saveJsonFileAs();
    void reloadJsonFile();

    void cloneSensor(Model::Sensore* sensor);
    void modifySensor(Model::Sensore* sensor);
    void deleteSensor(Model::Sensore* sensor);

    void onSearchTextChanged(const QString& searchText);
    void onFilterComboBoxChanged(const QString& sensorType);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static Model::Sensore* creaSensore(const QJsonObject& ) ;
    static QJsonObject mapToJson(const std::map<std::string, std::string>& ) ;

public slots:
    void onSensorSelected(const std::string sensorID);
    void dataUpdated();
    void onSensorModified(std::map<std::string, std::string>&);
};

#endif
