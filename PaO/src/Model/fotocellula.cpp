#include "fotocellula.h"

namespace Model{

Fotocellula::Fotocellula(unsigned int id, std::string nome, double s, double t) :
    Sensore(id,nome),
    attivo(false),
    soglia(s),
    tolleranza(t) {}

Fotocellula::Fotocellula(const QJsonObject& json) : Sensore(json) {
    attivo = json["Attivo"].toBool();
    soglia = json["Soglia"].toDouble();
    tolleranza = json["Tolleranza"].toDouble();
}

bool Fotocellula::isAttivo() const {
    return attivo;
}

void Fotocellula::simulaMisura() {
    // metodo da rifare, non vul dire nulla
    attivo=true;
}

bool Fotocellula::Misura(bool valoreReale) {
    return true;
}

double Fotocellula::getSoglia() const{
    return soglia;
}

double Fotocellula::getTolleranza() const{
    return tolleranza;
}

std::map<std::string, std::string> Fotocellula::getInfo() const {
    std::map<std::string, std::string> info= Sensore::getInfo();
    info.insert(std::make_pair("Attivo", attivo ? "true" : "false"));
    info.insert(std::make_pair("Soglia", std::to_string(soglia)));
    return info;
}

}
