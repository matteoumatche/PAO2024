#ifndef FOTOCELLULA_H
#define FOTOCELLULA_H

#include <map>
#include <string>
#include <QJsonObject>
#include "math.h"
#include "sensore.h"

namespace Model{

class Fotocellula : public Sensore {
private:

    bool attivo;
    double soglia;
    double tolleranza;

public:
    Fotocellula(unsigned int id, std::string n, double s=0, double t=0);
    Fotocellula(const QJsonObject& json);

    bool isAttivo() const;
    double getSoglia() const;
    double getTolleranza() const;
    std::map<std::string, std::string> getInfo() const;

    void simulaMisura() override;
    bool Misura(bool valoreReale);
};

}

#endif // FOTOCELLULA_H
