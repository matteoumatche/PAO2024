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
#include "src/View/toolbar.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* centralLayout;
    QWidget* centralWidget;
    View::ToolBar* tbar;

    QStringList getAvailableSensorTypes();

private slots:
    void addSensor(const QString &type, const QString &id);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void showNewSensorDialog();
};
#endif // MAINWINDOW_H