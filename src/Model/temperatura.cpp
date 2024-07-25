#include "temperatura.h"

namespace Model {

double Temperatura::zeroAssoluto = -273.15;

Temperatura::Temperatura(unsigned int id, std::string nome) :
    Sensore(id, nome),
    valoreMin(-10),
    valoreMax(100),
    valoreIdeale(20),
    tolleranza(0.1),
    dato(0) {}

Temperatura::Temperatura(unsigned int id, std::string nome, double toll, double min, double max, double ideale) :
    Sensore(id, nome),
    tolleranza(toll>0 ? toll : 0.1),
    dato(0) {

        if(min >= zeroAssoluto)        valoreMin =  std::round(min/ tolleranza) * tolleranza;
        else                           valoreMin = zeroAssoluto;

        valoreMax =  std::round(max/ tolleranza) * tolleranza;
        valoreIdeale =  std::round(ideale/ tolleranza) * tolleranza;
}

Temperatura::Temperatura(const QJsonObject& json) : Sensore(json) {
    valoreMin = json["Min"].toDouble();
    valoreMax = json["Max"].toDouble();
    valoreIdeale = json["ValoreIdeale"].toDouble();
    tolleranza = json["Tolleranza"].toDouble();
    dato = json["Dato"].toDouble();
}


double Temperatura::getMin() const {
    return valoreMin;
}

double Temperatura::getMax() const {
    return valoreMax;
}

double Temperatura::getValoreIdeale() const {
    return valoreIdeale;
}

double Temperatura::getDato() const {
    return dato;
}

double Temperatura::getTolleranza() const {
    return tolleranza;
}

bool Temperatura::isCold() const {
    return dato < valoreIdeale;
}

bool Temperatura::isHot() const {
    return dato > valoreIdeale;
}

void Temperatura::simulaMisura() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(valoreMin, valoreMax);
    //salvo il dato simulato assicurandomi che rispetti la precisione dello strumento
    dato = std::round(dis(gen)/ tolleranza) * tolleranza;
}

double Temperatura::Misura(double valoreReale) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-tolleranza, tolleranza);
    dato = std::round((valoreReale + dis(gen)) / tolleranza) * tolleranza;
    return dato;
}

QJsonObject Temperatura::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Min"] = getMin();
    json["Max"] = getMax();
    json["ValoreIdeale"] = getValoreIdeale();
    json["Tolleranza"] = getTolleranza();
    json["Dato"] = getDato();
    return json;
}

}
