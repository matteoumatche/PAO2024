#ifndef TEMPERCEPITA_H
#define TEMPERCEPITA_H

#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <QJsonObject>

#include "sensore.h"

namespace Model {

class TemPercepita : public Sensore {
private:
    Umidita u;
    Temperatura t;
    double IndiceCalore;
public:
    TemPercepita(unsigned int id, std::string nome, Umidita u, Temperatura t);
    TemPercepita(Temperatura t);
    double getIndiceCalore() const;
    void simulaMisura();
    double Misura(double);
};

}

#endif
