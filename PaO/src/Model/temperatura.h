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
    Temperatura(unsigned int id=0, std::string nome="temperatura", double toll = 0.5);
    Temperatura(const QJsonObject& json);

    double getTolleranza() const;
    double getDato() const;
    std::map<std::string, std::string> getInfo() const override;

    void setTolleranza(double tolleranza);

    void simulaMisura() override;
    double Misura(double valoreReale);

    virtual Temperatura* clone() const override; // Metodo clone
};

}

#endif // TEMPERATURA_H
