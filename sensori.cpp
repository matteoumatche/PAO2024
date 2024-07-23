#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include "math.h"

//--------------------Sensore--------------------
class Sensore {
private:
    unsigned int ID;
    std::string nome;
public:
    Sensore(unsigned int id, std::string nome);
    Sensore(const QJsonObject& json);
    /*ho eliminato il distruttore e il costruttore di copia perchè vanno bene quelli standard*/

    std::string getNome() const;
    unsigned int getID() const;
    void setNome(std::string n);
    QJsonObject salva() const;

    virtual void simulaMisura() = 0;
};

Sensore::Sensore(unsigned int id, std::string n) : ID(id), nome(n) {}

Sensore::Sensore(const QJsonObject& json) : ID(json["ID"].toInt()), nome(json["Nome"].toString().toStdString()) {}

std::string Sensore::getNome() const {
    return nome;
}

unsigned int Sensore::getID() const {
    return ID;
}

void Sensore::setNome(std::string n) {
    nome=n;
}

QJsonObject Sensore::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(ID);
    json["Nome"] = QString::fromStdString(nome);
    return json;
}


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

QJsonObject Fotocellula::salva() const {
    QJsonObject json = Sensore::salva();
    json["Tipo"] = "Fotocellula";
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Attivo"] = isAttivo();
    json["Soglia"] = getSoglia();
    json["Tolleranza"] = getTolleranza();
    return json;
}


//--------------------Vento--------------------
class Vento : public Sensore {
private:
    double valoreMaxVelocita;   //questo è const? Essendo valore massimo
    double tolleranzaGoniometro;
    double tolleranzaAnemometro;
    double offset;
    std::pair<double, double> dato;

public:
    double limitaAngolo(double x) const {
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
    }
    Vento(unsigned int id, std::string n,double o);
    Vento(QJson dato);
    Vento(unsigned int id, std::string n,double o=0, double max=30, double tollG=0.1, double tollA=0.5);
    Vento(const QJsonObject& json);
    //--------------------getter--------------------
    double getMaxVelocita() const;
    double getOffset() const;
    double getTolleranzaGoniometro() const;
    double getTolleranzaAnemometro() const;
    std::pair<double, double> getDato() const;
    //--------------------metodi--------------------
    void setOffset(double offset);
    void simulaMisura();
    std::pair<double, double> Misura(std::pair<double, double> valoreReale);
    QJsonObject salva() const;
};

Vento::Vento(unsigned int id, std::string n, double o) : 
    Sensore(id, n),
    offset(limitaAngolo(o)),
    valoreMaxVelocita(30), 
    tolleranzaGoniometro(0.1), 
    tolleranzaAnemometro(0.5), 
    dato(std::make_pair(0, 0)) {}    

Vento::Vento(unsigned int id, std::string n,double o, double max, double tollG, double tollA) : 
    Sensore(id, n), 
    valoreMaxVelocita(max>0 ? max : 30), 
    tolleranzaGoniometro(limitaAngolo(tollG)?limitaAngolo(tollG):0.1), 
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
    double angolo = std::round((limitaAngolo(valoreReale.second + disv(gen))) / tolleranzaGoniometro) * tolleranzaGoniometro;
    dato = std::make_pair(velocita, angolo);
    return dato;
}

QJsonObject Vento::salva() const {
    QJsonObject json= Sensore::salva();
    json["Tipo"] = "Vento";
    json["Offset"] = getOffset();
    json["MaxVelocita"] = getMaxVelocita();
    json["TolleranzaGoniometro"] = getTolleranzaGoniometro();
    json["TolleranzaAnemometro"] = getTolleranzaAnemometro();
    json["Dato"] = QJsonObject{
        {"Velocita", getDato().first},
        {"Angolo", getDato().second}
    };
    return json;
}


//--------------------Temperatura--------------------
class Temperatura : public Sensore {
private:
    double valoreMin;
    double valoreMax;
    /*const*/ double valoreIdeale;
    double tolleranza;  //unsigned int? No, ma simile? const?
    double dato;
    static double zeroAssoluto;
public:
    Temperatura(unsigned int id, std::string nome);
    Temperatura(unsigned int id, std::string nome, double min, double max, double ideale, double toll);
    //--------------------getter--------------------
    double getMin() const;
    double getMax() const;
    double getDato() const;
    double getTolleranza() const;
    bool isCold() const;
    bool isHot() const;
    
    //--------------------metodi--------------------
    void simulaMisura();
    double Misura(double);
};

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
    QJsonObject json= Sensore::salva();
    json["Tipo"] = "Temperatura";
    json["Min"] = getMin();
    json["Max"] = getMax();
    json["ValoreIdeale"] = getValoreIdeale();
    json["Tolleranza"] = getTolleranza();
    json["Dato"] = getDato();
    return json;
}


//--------------------Umidita--------------------
class Umidita : public Sensore {
private:
    double valoreMin;
    double valoreMax;
    std::pair<double,double> rangeOttimale;
    double tolleranza;
    double dato;
public:
    Umidita(unsigned int id, std::string n);
    Umidita(unsigned int id, std::string n, double min, double max, std::pair<double,double> range, double toll);
    Umidita(const QJsonObject& json);
    //--------------------getter--------------------
    double getMin() const;
    double getMax() const;
    double getDato() const;
    double getTolleranza() const;
    //--------------------metodi--------------------
    bool outOfRange() const;
    void simulaMisura();
    double Misura(double);
    QJsonObject salva() const;
};

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
    QJsonObject json= Sensore::salva();
    json["Tipo"] = "Umidita";
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


//--------------------TemPercepita--------------------
class TemPercepita : public Sensore {
private:
    Umidita u;
    Temperatura t;
    double IndiceCalore;
public:
    TemPercepita(unsigned int id, std::string nome, Umidita u, Temperatura t);
    TemPercepita(const QJsonArray& json);
    TemPercepita(Temperatura t);
    double getIndiceCalore() const;
    void simulaMisura();
    double Misura(double);
    QJsonObject salva() const;
};

TemPercepita::TemPercepita(unsigned int id, std::string nome, Umidita u, Temperatura t) : Sensore(id,nome), u(u), t(t)  {
    if(t.getDato()>27)    
        IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    else                  
        IndiceCalore = t.getDato();
}


TemPercepita::TemPercepita(Temperatura t) : t(t) , u(0, "umidita"){
    if(t.getDato()>27)   
     IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    else                 
     IndiceCalore = t.getDato();
}

TemPercepita::TemPercepita(const QJsonArray& json) : Sensore(json) {
    u = Umidita(json["Umidita"].toObject());
    t = Temperatura(json["Temperatura"].toObject());
    IndiceCalore = json["IndiceCalore"].toDouble();
}


double TemPercepita::getIndiceCalore() const {
    return IndiceCalore;
}

void TemPercepita::simulaMisura() {
    u.simulaMisura();
    t.simulaMisura();
    IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
}

double TemPercepita::Misura(double valoreReale) {
    u.Misura(valoreReale);
    t.Misura(valoreReale);
    IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    return IndiceCalore;
}

QJsonObject TemPercepita::salva() const {
    QJsonObject json = Sensore::salva();
    json["Tipo"] = "TemPercepita";
    json["Umidita"] = u.salva();
    json["Temperatura"] = t.salva();
    json["IndiceCalore"] = getIndiceCalore();
    return json;
}


class Sensori {
    private:
        std::vector<Sensore*> sensori;
    public:
        explicit Sensori();
        Sensori(const QJsonArray& json);
        ~Sensori();
        void aggiungi(Sensore* s);
        void rimuovi(unsigned int id);
        Sensore* get(unsigned int id) const;
        QJsonArray salva() const;
};

sensori::Sensori(const QJlsonObject json) {}

void Sensori::aggiungi(Sensore* s) {
    void Sensori::aggiungi(Sensore* s) {
        sensori.push_back(s);
    }
}
Sensori::Sensori() {}

Sensori::Sensori(const QJsonArray& json) {
    for (const auto& sensoriJson : json) {
        QJsonObject sensoriObj = sensoriJson.toObject();
        std::string tipo = sensoriObj["Tipo"].toString().toStdString();
        if (tipo == "Fotocellula") {
            Fotocellula* f = new Fotocellula(sensoriObj);
            aggiungi(f);
        } else if (tipo == "Vento") {
            Vento* v = new Vento(sensoriObj);
            aggiungi(v);
        } else if (tipo == "Temperatura") {
            Temperatura* t = new Temperatura(sensoriObj);
            aggiungi(t);
        } else if (tipo == "Umidita") {
            Umidita* u = new Umidita(sensoriObj);
            aggiungi(u);
        } else if (tipo == "TemPercepita") {
            TemPercepita* tp = new TemPercepita(sensoriObj);
            aggiungi(tp);
        }
    }
}

Sensori::~Sensori() {
    for (Sensore* s : sensori) {
        delete s;
    }
}

void Sensori::aggiungi(Sensore* s) {
    sensori.push_back(s);
}

void Sensori::rimuovi(unsigned int id) {
    for (auto it = sensori.begin(); it != sensori.end(); ++it) {
        if ((*it)->getID() == id) {
            delete *it;
            sensori.erase(it);
            it=sensori.end();
        }
    }
}

Sensore* Sensori::get(unsigned int id) const {
    for (Sensore* s : sensori) {
        if (s->getID() == id) {
            return s;
        }
    }
    return nullptr;
}

QJsonArray Sensori::salva() const {
    
    QJsonArray sensoriArray;
    for (Sensore* s : sensori) {
        sensoriArray.append(s.salva());
    }
    
    return sensoriArray;
}

int main() {
     
    Fotocellula f(2, "fotocellula");
    Vento v(3, "vento");
    Temperatura t(4, "temperatura");
    Umidita u(5, "umidita");
    
    v.simulaMisura();
    t.simulaMisura();
    u.simulaMisura();

    

    std::cout << "-------simulamisura---------"<< std::endl;
    std::cout << "ID: " << f.getID() << " Nome: " << f.getNome() << " misurazione: "  << f.isAttivo() << std::endl;
    std::cout << "ID: " << v.getID() << " Nome: " << v.getNome() << " misurazione: "  << v.getDato().first << " " <<  v.getDato().second << std::endl;
    std::cout << "ID: " << t.getID() << " Nome: " << t.getNome() << " misurazione: "  << t.getDato()<< std::endl;
    std::cout << "ID: " << u.getID() << " Nome: " << u.getNome() << " misurazione: "  << u.getDato()<< std::endl;

    v.Misura(std::make_pair(10, 180));
    t.Misura(20);
    u.Misura(10);

    std::cout << "-------misura---------"<< std::endl;
    std::cout << "ID: " << f.getID() << " Nome: " << f.getNome() << " misurazione: "  << f.isAttivo() << std::endl;
    std::cout << "ID: " << v.getID() << " Nome: " << v.getNome() << " misurazione: "  << v.getDato().first << " " <<  v.getDato().second << std::endl;
    std::cout << "ID: " << t.getID() << " Nome: " << t.getNome() << " misurazione: "  << t.getDato()<< std::endl;
    std::cout << "ID: " << u.getID() << " Nome: " << u.getNome() << " misurazione: "  << u.getDato()<< std::endl;


    return 0;
}