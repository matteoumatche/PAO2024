#include "fotocellula.h"

namespace Model {

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

double Fotocellula::getSoglia() const {
    return soglia;
}

double Fotocellula::getTolleranza() const {
    return tolleranza;
}

void Fotocellula::simulaMisura() { 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(valoreMin, valoreMax);
    //salvo il dato simulato assicurandomi che rispetti la precisione dello strumento
    if(soglia < std::round(dis(gen)/ tolleranza) * tolleranza);
    attivo=true;
}

bool Fotocellula::Misura(bool valoreReale) {
    
}

QJsonObject Fotocellula::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Attivo"] = isAttivo();
    json["Soglia"] = getSoglia();
    json["Tolleranza"] = getTolleranza();
    return json;
}

}
