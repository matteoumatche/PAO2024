#include "umidita.h"

namespace Model {

Umidita::Umidita(unsigned int id, std::string n) :
    Sensore(id, n),
    valoreMin(0),
    valoreMax(30),
    rangeOttimale(std::make_pair(5, 100)),
    tolleranza(0.1),
    dato(0) {
}
Umidita::Umidita(unsigned int id, std::string n, double min, double max, std::pair<double,double> range, double toll) :
    Sensore(id, n),
    valoreMin(min>0 ? min : 0),
    valoreMax(max>0 && max>= 100 ? max : 30),
    rangeOttimale(range),
    tolleranza(toll>0 ? toll : 0.1),
    dato(0) {
        //da inserire controllo su range , min e max
}

Umidita::Umidita(const QJsonObject& json) : Sensore(json) {
    valoreMin = json["Min"].toDouble();
    valoreMax = json["Max"].toDouble();
    rangeOttimale.first = json["RangeOttimale"].toObject()["Min"].toDouble();
    rangeOttimale.second = json["RangeOttimale"].toObject()["Max"].toDouble();
    tolleranza = json["Tolleranza"].toDouble();
    dato = json["Dato"].toDouble();
}

double Umidita::getMin() const {
    return valoreMin;
}

double Umidita::getMax() const {
    return valoreMax;
}

double Umidita::getDato() const {
    return dato;
}

double Umidita::getTolleranza() const {
    return tolleranza;
}

bool Umidita::outOfRange() const {
    return dato < rangeOttimale.first || dato > rangeOttimale.second;
}

void Umidita::simulaMisura() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(valoreMin, valoreMax);
    dato = std::round(dis(gen) / tolleranza) * tolleranza;
}

double Umidita::Misura(double valoreReale) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-tolleranza, tolleranza);
    dato= std::round((valoreReale + dis(gen)) / tolleranza) * tolleranza;
    return dato;
}

QJsonObject Umidita::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Min"] = getMin();
    json["Max"] = getMax();
    json["RangeOttimale"] = QJsonObject{
        {"Min", rangeOttimale.first},
        {"Max", rangeOttimale.second}
    };
    json["Tolleranza"] = getTolleranza();
    json["Dato"] = getDato();
    return json;
}

}
