#ifndef EDITSENSORDIALOG_H
#define EDITSENSORDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include "../Model/sensore.h"
#include "../Model/temperatura.h"
#include "../Model/umidita.h"
#include "../Model/tempercepita.h"
#include "../Model/vento.h"
#include "../Model/fotocellula.h"
#include "../mainwindow.h"

namespace Model {
    class Sensore;  // Forward declaration
}

class EditSensorDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditSensorDialog(Model::Sensore* sensore,std::vector<Model::Sensore*>& sensori, QWidget* parent = nullptr);
    ~EditSensorDialog();



private slots:
    void acceptChanges(Model::Sensore*);

private:
    //Model::Sensore* sensore;
    std::map<std::string, QLineEdit*> edits;  // Mappa per associare chiavi della mappa del sensore a QLineEdit
};

#endif
