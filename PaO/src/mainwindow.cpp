#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mainLayout(nullptr), centralLayout(nullptr), centralWidget(nullptr), tbar(nullptr)
{
    setWindowTitle("Sensori serra");

    //layout
    mainLayout = new QVBoxLayout;
    centralLayout = new QHBoxLayout;

    //pannello principale
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    tbar->setFixedSize(1024, 30);

    mainLayout->addWidget(tbar);
}

MainWindow::~MainWindow(){}
