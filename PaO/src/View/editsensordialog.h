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

namespace Model {
    class Sensore;  // Forward declaration
}

class EditSensorDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditSensorDialog(Model::Sensore* sensore, QWidget* parent = nullptr);

    double getValore1() const; // Getter per il primo valore
    double getValore2() const; // Getter per il secondo valore

private slots:
    void acceptChanges();

private:
    Model::Sensore* sensore;
    std::map<std::string, QLineEdit*> edits;  // Mappa per associare chiavi della mappa del sensore a QLineEdit
};

#endif
