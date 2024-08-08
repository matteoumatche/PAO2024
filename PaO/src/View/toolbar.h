#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QToolButton>
#include <string>
#include <QFormLayout>


namespace View {

class ToolBar : public QToolBar {
    Q_OBJECT

private:
    QAction* newAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;



signals:
    void newSignal();
    void openSignal();
    void saveSignal();
    void saveAsSignal();
    void fileOpened();
    void setIsSaved(const bool& value);

public slots:
    void newSlot();
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
    void saveJsonFile(int, std::string nomeFile);//fuffa
    void saveJsonFileAs(int, std::string nomeFile);//fuffa

    ~ToolBar();
};

}

#endif
