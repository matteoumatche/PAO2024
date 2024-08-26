#include "vento.h"
#include <random>
#include <cmath>
#include <QJsonDocument>

namespace Model{

Vento::Vento(unsigned int id, std::string n, double o) :
    Sensore(id, n),
    offset(limitaAngolo(o)),
    valoreMaxVelocita(30),
    tolleranzaGoniometro(0.1),
    tolleranzaAnemometro(0.5),
    dato(std::make_pair(0, 0)) {}

Vento::Vento(unsigned int id, std::string n, double o, double max, double tollG, double tollA) :
    Sensore(id, n),
    valoreMaxVelocita(max>0 ? max : 30),
    tolleranzaGoniometro(limitaAngolo(tollG) ? limitaAngolo(tollG) : 0.1),
    tolleranzaAnemometro(tollA>0 ? tollA : 0.5),
    dato(std::make_pair(0, 0)) {
    offset = std::round(limitaAngolo(o)*tolleranzaGoniometro) * tolleranzaGoniometro;
}

Vento::Vento(const QJsonObject& json) : Sensore(json) {
    auto stringToDouble = [](const QString& str) -> double {
        bool ok;
        double value = str.toDouble(&ok);
        return ok ? value : 0.0;
    };

    if (json.contains("Offset") && json["Offset"].isString()) {
        offset = stringToDouble(json["Offset"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'Offset' in JSON";
        offset = 0.0;
    }

    if (json.contains("MaxVelocita") && json["MaxVelocita"].isString()) {
        valoreMaxVelocita = stringToDouble(json["MaxVelocita"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'MaxVelocita' in JSON";
        valoreMaxVelocita = 30.0;
    }

    if (json.contains("TolleranzaGoniometro") && json["TolleranzaGoniometro"].isString()) {
        tolleranzaGoniometro = stringToDouble(json["TolleranzaGoniometro"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'TolleranzaGoniometro' in JSON";
        tolleranzaGoniometro = 0.1;
    }

    if (json.contains("TolleranzaAnemometro") && json["TolleranzaAnemometro"].isString()) {
        tolleranzaAnemometro = stringToDouble(json["TolleranzaAnemometro"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'TolleranzaAnemometro' in JSON";
        tolleranzaAnemometro = 0.5;
    }

    if (json.contains("Velocita") && json["Velocita"].isString()) {
        dato.first = stringToDouble(json["Velocita"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'Velocita' in 'Dato' object";
        dato.first = 0.0;
    }

    if (json.contains("Angolo") && json["Angolo"].isString()) {
        dato.second = stringToDouble(json["Angolo"].toString());
    } else {
        qDebug() << "Warning: Missing or incorrect 'Angolo' in 'Dato' object";
        dato.second = 0.0;
    }
}

double Vento::limitaAngolo(double x) const {
    x = fmod(x, 360);
    if (x < 0)
        x += 360;
    return x;
}

double Vento::getOffset() const {
    return offset;
}

double Vento::getMaxVelocita() const {
    return valoreMaxVelocita;
}

std::pair<double, double> Vento::getDato() const {
    return dato;
}

double Vento::getTolleranzaGoniometro() const {
    return tolleranzaGoniometro;
}

double Vento::getTolleranzaAnemometro() const {
    return tolleranzaAnemometro;
}

void Vento::setOffset(double o) {
    offset = o;
}

void Vento::setTolleranzaGoniometro(double tg) {
    tolleranzaGoniometro = tg;
}

void Vento::setTolleranzaAnemometro(double ta) {
    tolleranzaAnemometro = ta;
}

void Vento::simulaMisura() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disv(0, valoreMaxVelocita);
    std::uniform_real_distribution<> disa(0, 360);
    double velocita = std::round(disv(gen)/tolleranzaAnemometro) * tolleranzaAnemometro;
    double angolo = std::round(disa(gen)/tolleranzaGoniometro) * tolleranzaGoniometro;
    dato = std::make_pair(velocita, angolo);
}

std::pair<double, double> Vento::Misura(std::pair<double, double> valoreReale) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disv(-tolleranzaAnemometro, tolleranzaAnemometro);
    std::uniform_real_distribution<> disa(-tolleranzaGoniometro, tolleranzaGoniometro);
    double velocita = std::round((valoreReale.first + disv(gen)) / tolleranzaAnemometro) * tolleranzaAnemometro;
    double angolo = std::round((limitaAngolo(valoreReale.second + offset) + disa(gen)) / tolleranzaGoniometro) * tolleranzaGoniometro;
    dato = std::make_pair(velocita, limitaAngolo(angolo));
    return dato;
}

std::map<std::string, std::string> Vento::getInfo() const {
    std::map<std::string, std::string> info;
    info.merge(Sensore::getInfo());
    info.insert(std::make_pair("Tipo", "Vento"));
    info.insert(std::make_pair("Offset", std::to_string(offset)));
    info.insert(std::make_pair("MaxVelocita", std::to_string(valoreMaxVelocita)));
    info.insert(std::make_pair("TolleranzaGoniometro", std::to_string(tolleranzaGoniometro)));
    info.insert(std::make_pair("TolleranzaAnemometro", std::to_string(tolleranzaAnemometro)));
    info.insert(std::make_pair("Velocita", std::to_string(dato.first)));
    info.insert(std::make_pair("Angolo", std::to_string(dato.second)));
    return info;
}

Vento* Vento::clone() const {
    return new Vento(*this);
}

}
