#include "Vento.h"
#include <random>
#include <cmath>

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
    offset = json["Offset"].toDouble();
    valoreMaxVelocita = json["MaxVelocita"].toDouble();
    tolleranzaGoniometro = json["TolleranzaGoniometro"].toDouble();
    tolleranzaAnemometro = json["TolleranzaAnemometro"].toDouble();
    dato.first = json["Dato"].toObject()["Velocita"].toDouble();
    dato.second = json["Dato"].toObject()["Angolo"].toDouble();
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

QJsonObject Vento::salva() const {
    QJsonObject json = Sensore::salva();
    json["Tipo"] = "Vento";
    json["MaxVelocita"] = getMaxVelocita();
    json["Offset"] = getOffset();
    json["TolleranzaGoniometro"] = getTolleranzaGoniometro();
    json["TolleranzaAnemometro"] = getTolleranzaAnemometro();
    QJsonObject datoJson;
    datoJson["Velocita"] = dato.first;
    datoJson["Angolo"] = dato.second;
    json["Dato"] = datoJson;
    return json;
}

void Vento::setOffset(double o){
    offset = o;
}
