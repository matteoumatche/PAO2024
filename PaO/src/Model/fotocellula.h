#ifndef FOTOCELLULA_H
#define FOTOCELLULA_H

#include <string>
#include <QJsonObject>
#include "math.h"
#include "sensore.h"

class Fotocellula : public Sensore {
private:
    bool attivo;
    double soglia;
    double tolleranza;

public:
    Fotocellula(unsigned int id, std::string n, double s, double t);
    Fotocellula(const QJsonObject& json);

    bool isAttivo() const;
    double getSoglia() const;
    double getTolleranza() const;

    void simulaMisura() override;
    bool Misura(bool valoreReale);
    QJsonObject salva() const override;
};



#endif // FOTOCELLULA_H
