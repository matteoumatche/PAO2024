#include "temperatura.h"
#include <random>

namespace Model{

Temperatura::Temperatura(unsigned int id, std::string nome, double toll) :
    Sensore(id, nome),
    tolleranza(toll > 0 ? toll : 0.5),
    dato(0) {}

Temperatura::Temperatura(const QJsonObject& json) : Sensore(json) {
    tolleranza = json["Tolleranza"].toDouble();
    dato = json["Dato"].toDouble();
}

double Temperatura::getTolleranza() const {
    return tolleranza;
}

double Temperatura::getDato() const {
    return dato;
}

void Temperatura::simulaMisura() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10, 40);
    dato = std::round(dis(gen) / tolleranza) * tolleranza;
}

double Temperatura::Misura(double valoreReale) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-tolleranza, tolleranza);
    dato = std::round((valoreReale + dis(gen)) / tolleranza) * tolleranza;
    return dato;
}

std::map<std::string, std::string> Temperatura::getInfo() const {
    std::map<std::string, std::string> info;
    info.merge(Sensore::getInfo());
    info.insert(std::make_pair("Tipo", "Temperatura"));
    info.insert(std::make_pair("Tolleranza", std::to_string(tolleranza)));
    info["Dato"] = std::to_string(dato);
    return info;
}

}
