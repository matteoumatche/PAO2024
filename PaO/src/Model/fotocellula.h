#ifndef FOTOCELLULA_H
#define FOTOCELLULA_H

#include "Sensore.h"

namespace Model{

class Fotocellula : public Sensore {
private:

    bool attivo;
    double soglia;

public:
    Fotocellula(unsigned int id, std::string n, double s=0);
    Fotocellula(const QJsonObject& json);

    bool isAttivo() const;
    double getSoglia() const;
    std::map<std::string, std::string> getInfo() const override;

    void setSoglia(double soglia);

    void simulaMisura() override;
    bool Misura(bool valoreReale);

    Fotocellula* clone() const override;
};

}

#endif
