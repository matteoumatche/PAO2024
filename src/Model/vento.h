#ifndef VENTO_H
#define VENTO_H

#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <QJsonObject>

#include "sensore.h"

namespace Model {

class Vento : public Sensore {
private:
    double valoreMaxVelocita;   //questo è const? Essendo valore massimo
    double tolleranzaGoniometro;
    double tolleranzaAnemometro;
    double offset;
    std::pair<double, double> dato;

public:
    double limitaAngolo(double x) const {
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
    }
    Vento(unsigned int id, std::string n,double o);
    Vento(QJson dato);
    Vento(unsigned int id, std::string n,double o=0, double max=30, double tollG=0.1, double tollA=0.5);
    Vento(const QJsonObject& json);
    //--------------------getter--------------------
    double getMaxVelocita() const;
    double getOffset() const;
    double getTolleranzaGoniometro() const;
    double getTolleranzaAnemometro() const;
    std::pair<double, double> getDato() const;
    //--------------------metodi--------------------
    void setOffset(double offset);
    void simulaMisura();
    std::pair<double, double> Misura(std::pair<double, double> valoreReale);
    QJsonObject salva() const;
};

}

#endif
