#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include "Sensore.h"

class Temperatura : public Sensore {
private:
    double tolleranza;
    double dato;

public:
    Temperatura(unsigned int id, std::string nome, double toll = 0.5);
    Temperatura(const QJsonObject& json);

    double getTolleranza() const;
    double getDato() const;

    void simulaMisura() override;
    double Misura(double valoreReale);
    QJsonObject salva() const override;
};

#endif // TEMPERATURA_H
