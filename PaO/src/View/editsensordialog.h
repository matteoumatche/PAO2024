// editsensordialog.h

#ifndef EDITSENSORDIALOG_H
#define EDITSENSORDIALOG_H

#include <QDialog>
#include <QMap>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QJsonObject>
#include "../Model/sensore.h"



class EditSensorDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditSensorDialog(Model::Sensore* sensore, QWidget* parent = nullptr);

signals:
    // Segnale che viene emesso quando il sensore viene modificato
    void sensorModified(std::map<std::string, std::string>&);

protected:
    // Sovrascrivi la funzione accept per gestire l'accettazione del dialogo
    void accept() override;

private:
    Model::Sensore* originalSensor;  // Puntatore al sensore originale
    std::map<std::string, QLineEdit*> editFields;  // Mappa per tenere traccia dei campi di modifica
};


#endif // EDITSENSORDIALOG_H
