#include "umidita.h"
#include <random>

namespace Model{

Umidita::Umidita(unsigned int id, std::string nome, double toll) :
    Sensore(id, nome),
    tolleranza(toll > 0 ? toll : 0.5),
    dato(0) {}

Umidita::Umidita(const QJsonObject& json) : Sensore(json) {
    auto stringToDouble = [](const QString& str) -> double {
        bool ok;
        double value = str.toDouble(&ok);
        return ok ? value : 0.0;
    };

    if (json.contains("Tolleranza") && json["Tolleranza"].isString()) {
        tolleranza = stringToDouble(json["Tolleranza"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'Tolleranza' in JSON";
        tolleranza = false;
    }

    if (json.contains("Dato") && json["Dato"].isString()) {
        dato = stringToDouble(json["Dato"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'Dato' in JSON";
        dato = false;
    }
}

double Umidita::getTolleranza() const {
    return tolleranza;
}

double Umidita::getDato() const {
    return dato;
}

void Umidita::setTolleranza(double t) {
    tolleranza = t;
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

std::map<std::string, std::string> Umidita::getInfo() const {
    std::map<std::string, std::string> info;
    info.merge(Sensore::getInfo());
    info.insert(std::make_pair("Tipo", "Umidità"));
    info.insert(std::make_pair("Tolleranza", std::to_string(tolleranza)));
    info["Dato"] = std::to_string(dato);
    return info;
}

Umidita* Umidita::clone() const {
    return new Umidita(*this);
}

}
