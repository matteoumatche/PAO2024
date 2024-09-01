#include "fotocellula.h"

#include <random>

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
    //ora corrente
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);

    //estrae l'ora del giorno (0 - 23)
    int hour = local_time->tm_hour;

    //probabilità base
    double probability = 0.0;

    //curva a campana che ha il picco tra le 10:00 e le 18:00
    if (hour >= 10 && hour <= 18) {
        //alle 14:00 (il picco), più alta la probabilità
        int peak_hour = 14;
        int distance_from_peak = std::abs(hour - peak_hour);
        probability = std::exp(-0.5 * std::pow(distance_from_peak / 2.0, 2)); // Gaussiana centrata sulle 14:00
    } else {
        //probabilità molto bassa al di fuori dell'orario di punta
        probability = 0.1;
    }

    //generazione casuale
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    attivo = (dis(gen) < probability);
}


bool Fotocellula::Misura(std::tm* local_time) {
    //estrae l'ora del giorno (0 - 23) dall'oggetto std::tm
    int hour = local_time->tm_hour;

    //probabilità base
    double probability = 0.0;

    //curva a campana che ha il picco tra le 10:00 e le 18:00
    if (hour >= 10 && hour <= 18) {
        //alle 14:00 (il picco), più alta la probabilità
        int peak_hour = 14;
        int distance_from_peak = std::abs(hour - peak_hour);
        probability = std::exp(-0.5 * std::pow(distance_from_peak / 2.0, 2)); // Gaussiana centrata sulle 14:00
    } else {
        //probabilità molto bassa al di fuori dell'orario di punta
        probability = 0.1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    return (dis(gen) < probability);
}

double Fotocellula::getSoglia() const{
    return soglia;
}

std::map<std::string, std::string> Fotocellula::getInfo() const {
    std::map<std::string, std::string> info;
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
