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
#include <vector>
#include "src/View/toolBar.h"
#include "src/Model/sensore.h"
#include "src/Model/fotocellula.h"
#include "src/Model/temperatura.h"
#include "src/Model/tempercepita.h"
#include "src/Model/umidita.h"
#include "src/Model/vento.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* centralLayout;
    QWidget* centralWidget;
    View::ToolBar* tbar;

    std::vector<Model::Sensore*> sensori;
    QString pathToFile;

    Model::Sensore* creaSensore(const QJsonObject& ) const ;
    QJsonObject mapToJson(const std::map<std::string, std::string>& ) const;
    QStringList getAvailableSensorTypes();

private slots:

    void addSensor(const QString &name, const QString &type, const QString &id);
    void showNewSensorDialog();

    void openJsonFile();
    void saveJsonFile();
    void saveJsonFileAs();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:

};
#endif // MAINWINDOW_H
