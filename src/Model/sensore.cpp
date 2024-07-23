#include "sensore.h"

namespace Model {

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

}
