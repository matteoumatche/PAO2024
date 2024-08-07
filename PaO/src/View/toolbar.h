#ifndef TOOLBAR_H
#define TOOLBAR_H
#include "src/Model/sensori.h"
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QToolButton>
#include <string>

namespace View {

class ToolBar : public QToolBar {
    Q_OBJECT

private:
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;

signals:
    void openSignal();
    void saveSignal();
    void saveAsSignal();
    void fileOpened();
    void setIsSaved(const bool& value);

public slots:
    void openSlot();
    void saveSlot();
    void saveAsSlot();

public:
    ToolBar(QToolBar *parent = nullptr);

    void activateSaveAction();
    void activateSaveAsAction();
    void disactivateSaveAction();
    void disactivateSaveAsAction();
    void openJsonFile();
    void saveJsonFile(Sensori sensors, std::string nomeFile);
    void saveJsonFileAs(Sensori sensors, std::string nomeFile);

    ~ToolBar();
};

}

#endif
