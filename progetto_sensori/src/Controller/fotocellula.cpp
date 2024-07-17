#include <iostream>
#include <random>
#include <functional>
#include <string>
#include "math.h"
#include "fotocellula.h"

//--------------------Fotocellula--------------------
class Fotocellula : public Sensore {
private:
    bool attivo;
    double soglia;
    double tolleranza;

public:
    Fotocellula(unsigned int id, std::string n, double s, double t);
    Fotocellula(const QJsonObject& json);
    
    bool isAttivo() const;

    void simulaMisura() override;
    bool Misura(bool valoreReale);
    QJsonObject salva() const;

    std::ostream& operator<<(std::ostream& os) const;
};

Fotocellula::Fotocellula(unsigned int id, std::string nome, double s, doule t) : 
Sensore(id,nome), 
attivo(false), 
soglia(s), 
tolleranza(t) {}

Fotocellula::Fotocellula(const QJsonObject& json) : Sensore(json) {
    attivo = json["Attivo"].toBool();
    soglia = json["Soglia"].toDouble();
    tolleranza = json["Tolleranza"].toDouble();
}

bool Fotocellula::isAttivo() const {
    return attivo;
}

void Fotocellula::simulaMisura() { 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(valoreMin, valoreMax);
    //salvo il dato simulato assicurandomi che rispetti la precisione dello strumento
    if(soglia < std::round(dis(gen)/ tolleranza) * tolleranza);
    attivo=true;
}

bool Fotocellula::Misura(bool valoreReale) {
    
}

std::ostream& Fotocellula::operator<<(std::ostream& os) const {
    return os << "ID fotocellula:" << getID() << "\n" << "Nome fotocellula:" << getNome() << "\n" << "Attivo?" << (isAttivo() ? "Sì" : "No") << std::endl;
}

QJsonObject Fotocellula::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Attivo"] = isAttivo();
    json["Soglia"] = getSoglia();
    json["Tolleranza"] = getTolleranza();
    return json;
}