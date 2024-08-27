#ifndef UMIDITA_H
#define UMIDITA_H

#include "Sensore.h"

namespace Model{

class Umidita : public Sensore {
private:
    double tolleranza;
    double dato;

public:
    Umidita(unsigned int id=0 , std::string n="umidita", double toll = 0.5);
    Umidita(const QJsonObject& );

    double getTolleranza() const;
    double getDato() const;
    std::map<std::string, std::string> getInfo() const override;

    void setTolleranza(double tolleranza);

    void simulaMisura() override;
    double Misura(double valoreReale);

    virtual Umidita* clone() const override;
};

}

#endif
