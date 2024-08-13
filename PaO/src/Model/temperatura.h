#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include "sensore.h"
#include <map>

namespace Model{

class Temperatura : public Sensore {
private:
    double tolleranza;
    double dato;

public:
    Temperatura(unsigned int id, std::string nome, double toll = 0.5);
    Temperatura(const QJsonObject& json);

    double getTolleranza() const;
    double getDato() const;
    std::map<std::string, std::string> getInfo() const override;

    void setTolleranza(double tolleranza);
    void setDato(double dato);

    void simulaMisura() override;
    double Misura(double valoreReale);

    virtual Temperatura* clone() const override; // Metodo clone
};

}

#endif // TEMPERATURA_H
