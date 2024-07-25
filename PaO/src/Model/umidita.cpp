#include "Umidita.h"
#include <random>

Umidita::Umidita(unsigned int id, std::string nome, double toll) :
    Sensore(id, nome),
    tolleranza(toll > 0 ? toll : 0.5),
    dato(0) {}

Umidita::Umidita(const QJsonObject& json) : Sensore(json) {
    tolleranza = json["Tolleranza"].toDouble();
    dato = json["Dato"].toDouble();
}

double Umidita::getTolleranza() const {
    return tolleranza;
}

double Umidita::getDato() const {
    return dato;
}

void Umidita::simulaMisura() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 100);
    dato = std::round(dis(gen) / tolleranza) * tolleranza;
}

double Umidita::Misura(double valoreReale) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-tolleranza, tolleranza);
    dato = std::round((valoreReale + dis(gen)) / tolleranza) * tolleranza;
    return dato;
}

QJsonObject Umidita::salva() const {
    QJsonObject json = Sensore::salva();
    json["Tipo"] = "Umidita";
    json["Tolleranza"] = getTolleranza();
    json["Dato"] = getDato();
    return json;
}
