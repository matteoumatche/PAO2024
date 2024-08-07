#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "src/View/toolBar.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget* centralWidget;
    QVBoxLayout* v;
    QHBoxLayout* h;
    View::ToolBar* tbar;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
