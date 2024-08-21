#include "fotocellula.h"

namespace Model{

Fotocellula::Fotocellula(unsigned int id, std::string nome, double s) :
    Sensore(id,nome),
    attivo(false),
    soglia(s) {}

Fotocellula::Fotocellula(const QJsonObject& json) : Sensore(json) {
    // Helper function to convert QString to double with error handling
    auto stringToDouble = [](const QString& str) -> double {
        bool ok;
        double value = str.toDouble(&ok);
        return ok ? value : 0.0; // Return 0.0 if conversion fails
    };

    // Helper function to convert QString to bool with error handling
    auto stringToBool = [](const QString& str) -> bool {
        return str.toLower() == "true"; // Convert "true" and "false" strings to bool
    };

    // Check and convert "Attivo"
    if (json.contains("Attivo") && json["Attivo"].isString()) {
        attivo = stringToBool(json["Attivo"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'Attivo' in JSON";
        attivo = false; // Default value
    }

    // Check and convert "Soglia"
    if (json.contains("Soglia")) {
        if (json["Soglia"].isString()) {
            soglia = stringToDouble(json["Soglia"].toString());
        } else {
            qDebug() << "Warning: 'Soglia' is of incorrect type in JSON";
            soglia = 0.0; // Default value
        }
    } else {
        qDebug() << "Warning: Missing 'Soglia' in JSON";
        soglia = 0.0; // Default value
    }

    /*
    attivo = json["Attivo"].toBool();
    soglia = json["Soglia"].toDouble();
    tolleranza = json["Tolleranza"].toDouble();
    */
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
    // Assuming Sensore::getInfo() returns a map
    std::map<std::string, std::string> sensorInfo = Sensore::getInfo();

    // Insert elements from sensorInfo into info
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
    // Supponendo che tu abbia un costruttore di copia
    return new Fotocellula(*this);
}

}
