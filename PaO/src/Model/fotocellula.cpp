#include "fotocellula.h"



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

QJsonObject Fotocellula::salva() const {
    QJsonObject json = Sensore::salva();
    json["Tipo"] = "Fotocellula";
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Attivo"] = isAttivo();
    json["Soglia"] = getSoglia();
    json["Tolleranza"] = getTolleranza();
    return json;
}
