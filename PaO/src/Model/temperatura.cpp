#include "temperatura.h"
#include <random>

namespace Model{

Temperatura::Temperatura(unsigned int id, std::string nome, double toll) :
    Sensore(id, nome),
    tolleranza(toll),
    dato(0) {}

Temperatura::Temperatura(const QJsonObject& json) : Sensore(json) {
    // Helper function to convert QString to double with error handling
    auto stringToDouble = [](const QString& str) -> double {
        bool ok;
        double value = str.toDouble(&ok);
        return ok ? value : 0.0; // Return 0.0 if conversion fails
    };

    // Check and convert "Tolleranza"
    if (json.contains("Tolleranza") && json["Tolleranza"].isString()) {
        tolleranza = stringToDouble(json["Tolleranza"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'Tolleranza' in JSON";
        tolleranza = 0.5; // Default value
    }

    // Check and convert "Dato"
    if (json.contains("Dato") && json["Dato"].isString()) {
        dato = stringToDouble(json["Dato"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'Dato' in JSON";
        dato = 0.0; // Default value
    }
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

void Temperatura::setTolleranza(double t) {
    tolleranza = t;
}

Temperatura* Temperatura::clone() const {
    // Supponendo che tu abbia un costruttore di copia
    return new Temperatura(*this);
}

}
