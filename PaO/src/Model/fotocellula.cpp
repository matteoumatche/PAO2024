#include "fotocellula.h"

namespace Model {

Fotocellula::Fotocellula(unsigned int id, std::string nome, double s) :
    Sensore(id,nome),
    attivo(false),
    soglia(s) {}

Fotocellula::Fotocellula(const QJsonObject& json) : Sensore(json) {
    auto stringToDouble = [](const QString& str) -> double {
        bool ok;
        double value = str.toDouble(&ok);
        return ok ? value : 0.0;
    };

    auto stringToBool = [](const QString& str) -> bool {
        return str.toLower() == "true";
    };

    if (json.contains("Attivo") && json["Attivo"].isString()) {
        attivo = stringToBool(json["Attivo"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'Attivo' in JSON";
        attivo = false;
    }

    if (json.contains("Soglia")) {
        if (json["Soglia"].isString()) {
            soglia = stringToDouble(json["Soglia"].toString());
        } else {
            qDebug() << "Warning: 'Soglia' is of incorrect type in JSON";
            soglia = 0.0;
        }
    } else {
        qDebug() << "Warning: Missing 'Soglia' in JSON";
        soglia = 0.0; // Default value
    }

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

std::map<std::string, std::string> Fotocellula::getInfo() const {
    std::map<std::string, std::string> info;
    //info.merge(Sensore::getInfo());
    std::map<std::string, std::string> sensorInfo = Sensore::getInfo();

    for (const auto& pair : sensorInfo) {
        info.insert(pair);
    }
    info.insert(std::make_pair("Tipo", "Fotocellula"));
    info.insert(std::make_pair("Attivo", attivo ? "true" : "false"));
    info.insert(std::make_pair("Soglia", std::to_string(soglia)));
    return info;
}

void Fotocellula::setSoglia(double s) {
    soglia = s;
}

Fotocellula* Fotocellula::clone() const {
    return new Fotocellula(*this);
}

}
