#include <iostream>
#include <random>
#include <functional>
#include <string>
#include "math.h"

//--------------------Sensore--------------------
class Sensore {
private:
    unsigned int ID;
    std::string nome;
public:
    Sensore(unsigned int id, std::string nome);
    /*ho eliminato il distruttore e il costruttore di copia perchè vanno bene quelli standard*/

    std::string getNome() const;
    unsigned int getID() const;
    void setNome(std::string n);

    virtual void simulaMisura() = 0;
};

Sensore::Sensore(unsigned int id, std::string n) : ID(id), nome(n) {}

std::string Sensore::getNome() const {
    return nome;
}

unsigned int Sensore::getID() const {
    return ID;
}

void Sensore::setNome(std::string n) {
    nome=n;
}


//--------------------Fotocellula--------------------
class Fotocellula : public Sensore {
private:
    bool attivo;
    double tempoRisposta;
public:
    Fotocellula(unsigned int id, std::string nome);
    
    bool isAttivo() const;

    void simulaMisura() override;
    bool Misura(bool valoreReale);
};

Fotocellula::Fotocellula(unsigned int id, std::string nome) : Sensore(id,nome), attivo(false) {}

bool Fotocellula::isAttivo() const {
    return attivo;
}

void Fotocellula::simulaMisura() { 
    attivo=true;
}

bool Fotocellula::Misura(bool valoreReale) {
    
}


//--------------------Vento--------------------
class Vento : public Sensore {
private:
    double valoreMaxVelocita;
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
    Vento(unsigned int id, std::string n,double o=0, double max=30, double tollG=0.1, double tollA=0.5);
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
};

Vento::Vento(unsigned int id, std::string n,double o) : 
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


//--------------------Temperatura--------------------
class Temperatura : public Sensore {
private:
    double valoreMin;
    double valoreMax;
    double valoreIdeale;
    double tolleranza;
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
    //--------------------getter--------------------
    double getMin() const;
    double getMax() const;
    double getDato() const;
    double getTolleranza() const;
    //--------------------metodi--------------------
    bool outOfRange() const;
    void simulaMisura();
    double Misura(double);
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
class TemPercepita {
private:
public:
};

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