#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <QJsonObject>

#include "sensore.h"

namespace Model {

class Temperatura : public Sensore {
private:
    double valoreMin;
    double valoreMax;
    /*const*/ double valoreIdeale;
    double tolleranza;  //unsigned int? No, ma simile? const?
    double dato;
    static double zeroAssoluto;
public:
    Temperatura(unsigned int id, std::string nome);
    Temperatura(unsigned int id, std::string nome, double min, double max, double ideale, double toll);
    //--------------------getter--------------------
    double getMin() const;
    double getMax() const;
    double getValoreIdeale() const;
    double getDato() const;
    double getTolleranza() const;
    bool isCold() const;
    bool isHot() const;

    //--------------------metodi--------------------
    void simulaMisura();
    double Misura(double);
    QJsonObject salva() const;
};

}

#endif
