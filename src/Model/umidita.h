#ifndef UMIDITA_H
#define UMIDITA_H

#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <QJsonObject>

#include "sensore.h"

namespace Model {

class Umidita : public Sensore {
private:
    double valoreMin;
    double valoreMax;
    std::pair<double,double> rangeOttimale;
    double tolleranza;
    double dato;
public:
    Umidita(unsigned int id, std::string n);
    Umidita(unsigned int id, std::string n, double min, double max, std::pair<double,double> range, double toll);
    Umidita(const QJsonObject& json);
    //--------------------getter--------------------
    double getMin() const;
    double getMax() const;
    double getDato() const;
    double getTolleranza() const;
    //--------------------metodi--------------------
    bool outOfRange() const;
    void simulaMisura();
    double Misura(double);
    QJsonObject salva() const;
};

}

#endif
