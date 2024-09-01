#include "toolbar.h"

#include <QDir>

namespace View {

ToolBar::ToolBar(QToolBar *parent)
    : QToolBar(parent)
{
    newAction = new QAction( tr("Nuovo sensore"), this);
    openAction = new QAction( tr("Apri"), this);
    saveAction = new QAction( tr("Salva"), this);
    saveAsAction = new QAction( tr("Salva con nome"), this);

    // QAction aggiunti alla ToolBar
    addAction(newAction);
    addAction(openAction);
    addAction(saveAction);
    addAction(saveAsAction);

    // Shortcut collegati ai QAction
    openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    newAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));

    saveAction->setEnabled(false);
    saveAsAction->setEnabled(false);

    //connect(newAction, &QAction::triggered, this, &MainWindow::showNewSensorDialog);
    connect(newAction, &QAction::triggered, this, &ToolBar::newSlot);
    connect(openAction, &QAction::triggered, this, &ToolBar::openSlot);
    connect(saveAction, &QAction::triggered, this, &ToolBar::saveSlot);
    connect(saveAsAction, &QAction::triggered, this, &ToolBar::saveAsSlot);
}

void ToolBar::newSlot(){
    emit newSignal();
}

void ToolBar::openSlot(){
    emit openSignal();
}

void ToolBar::saveSlot(){
    emit saveSignal();
}

void ToolBar::saveAsSlot(){
    emit saveAsSignal();
}

void ToolBar::activateSaveAction(){
    saveAction->setEnabled(true);
}

void ToolBar::activateSaveAsAction(){
    saveAsAction->setEnabled(true);
}

void ToolBar::disactivateSaveAction(){
    saveAction->setEnabled(false);
    //possibilità di salvare gli stessi dati in tanti file diversi
    //disactivateSaveAsActionAndButton per disattivare il "Salva con nome"
}

void ToolBar::disactivateSaveAsAction(){
    //quando l'utente ha eliminato tutti i sensori
    //non c'è niente da salvare con nome
    saveAsAction->setEnabled(false);
}

ToolBar::~ToolBar() //solo alla chiusura dell'app la ToolBar viene eliminata, non c'è mai una sovrascrizione a runtime,
{
    delete newAction;
    delete openAction;
    delete saveAction;
    delete saveAsAction;
}

}
