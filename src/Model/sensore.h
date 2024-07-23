#ifndef SENSORE_H
#define SENSORE_H

#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <QJsonObject>

#include "math.h"
#include "fotocellula.h"
#include "temperatura.h"
#include "tempercepita.h"
#include "umidita.h"
#include "vento.h"

namespace Model {

class Sensore {
private:
    unsigned int ID;
    std::string nome;
public:
    Sensore(unsigned int id, std::string nome);
    Sensore(const QJsonObject& json);

    std::string getNome() const;
    unsigned int getID() const;
    void setNome(std::string n);
    QJsonObject salva() const;

    virtual void simulaMisura() = 0;
};

}

#endif
