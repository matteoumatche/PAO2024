#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <vector>
#include "View/editsensordialog.h"
#include "src/View/toolBar.h"
#include "src/Model/sensore.h"
#include "src/Model/fotocellula.h"
#include "src/Model/temperatura.h"
#include "src/Model/tempercepita.h"
#include "src/Model/umidita.h"
#include "src/Model/vento.h"
#include "View/sensorlistwidget.h"
#include "View/sensorinfowidget.h"
#include "View/widgetgrafico.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* centralLayout;
    QHBoxLayout* searchLayout;
    QVBoxLayout* graphLayout;
    QHBoxLayout* optionsLayout;
    QVBoxLayout* dataLayout;
    QVBoxLayout* pulsantiLayout;
    QVBoxLayout* simulaLayout;
    QWidget* centralWidget;
    View::ToolBar* tbar;
    View::SensorListWidget* sensorListWidget;
    View::SensorInfoWidget* sensorInfoWidget;
    View::WidgetGrafico* graphWidget;
    QWidget* dataWidget;
    QVBoxLayout* sensorWidgetLayout;
    QScrollArea* scrollArea;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QPushButton *SimulaButton;
    //QPushButton *MisuraButton;

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
    // Slot per gestire la modifica del sensore
    void modifySensor(Model::Sensore* sensor);
      // Slot per gestire la modifica del sensore
    void deleteSensor(Model::Sensore* sensor);

    void onSearchButtonClicked();
    void onClearSearchButtonClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static Model::Sensore* creaSensore(const QJsonObject& ) ;
    static QJsonObject mapToJson(const std::map<std::string, std::string>& ) ;

public slots:
    void onSensorSelected(const std::string& sensorID);
    //aggiorna la finestra dopo la modifica dei dati
    void dataUpdated();
    void onSensorModified(std::map<std::string, std::string>&);

};
#endif // MAINWINDOW_H
