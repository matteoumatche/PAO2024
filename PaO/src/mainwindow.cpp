#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), centralWidget(nullptr),v(nullptr), h(nullptr), tbar(nullptr){
    v = new QVBoxLayout;
    h = new QHBoxLayout;


    tbar = new View::ToolBar();

    tbar->setFixedSize(1024, 30);

    v->addWidget(tbar);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(v);
}

MainWindow::~MainWindow(){}
