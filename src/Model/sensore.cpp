#include <iostream>
#include <random>
#include <functional>
#include <string>
#include "math.h"
#include "sensore.h"

//--------------------Sensore--------------------
class Sensore {
private:
    unsigned int ID;
    std::string nome;
public:
    Sensore(unsigned int id, std::string nome);
    Sensore(const QJsonObject& json);
    /*ho eliminato il distruttore e il costruttore di copia perchè vanno bene quelli standard*/

    std::string getNome() const;
    unsigned int getID() const;
    void setNome(std::string n);
    QJsonObject salva() const;

    virtual void simulaMisura() = 0;
};

Sensore::Sensore(unsigned int id, std::string n) : ID(id), nome(n) {}

Sensore::Sensore(const QJsonObject& json) : ID(json["ID"].toInt()), nome(json["Nome"].toString().toStdString()) {}

std::string Sensore::getNome() const {
    return nome;
}

unsigned int Sensore::getID() const {
    return ID;
}

void Sensore::setNome(std::string n) {
    nome=n;
}

QJsonObject Sensore::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(ID);
    json["Nome"] = QString::fromStdString(nome);
    return json;
}