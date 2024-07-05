#include <iostream>
#include <random>
#include <functional>
using namespace std;

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

    virtual void simulaMisura(){} ;
    bool Misura(bool valoreReale);
};

Fotocellula::Fotocellula(unsigned int id, std::string nome) : Sensore(id,nome), attivo(false) {}

//restituisce un true 70% delle volte
void Fotocellula::simulaMisura() {
       std::random_device rd;
    std::mt19937 gen(rd());

    // Genera un valore booleano con la probabilità specificata
    attivo=  gen() < 0.7 * gen.max();
}

bool Fotocellula::isAttivo() const {
    return attivo;
}

Fotocellula::Misura(bool valoreReale) {
    attivo=attivo&&simulaMisura();
}


//--------------------Vento--------------------
class Vento : public Sensore {
private:
    double valoreMaxVelocita;
    double tolleranzaGoniometro;
    double tolleranzaAnemometro;
    std::pair<double, double> dato;
public:
    Vento(unsigned int id, std::string nome);
    //--------------------getter--------------------
    double getMaxVelocita() const;
    double getoffset();
    double getTolleranzaGoniometro() const;
    double getTolleranzaAnemometro() const;
    std::pair<double, double> getDato() const;
    //--------------------metodi--------------------
    void simulaMisura();
    std::pair<double, double> Misura(std::pair<double, double> valoreReale);
};

Vento::Vento(unsigned int id, std::string nome) : Sensore(id, nome), valoreMaxVelocita(30), tolleranzaGoniometro(0.1), tolleranzaAnemometro(0.5), dato(std::make_pair(0, 0)) {}

double Vento::offset() {
    // Calcola l'offset tra la velocità massima e il valore attuale
    return valoreMaxVelocita - dato.first;
}

void Vento::setMaxVelocita(double maxVelocita) {
    valoreMaxVelocita = maxVelocita;
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
    std::uniform_real_distribution<> dis(0, valoreMaxVelocita);
    double velocita = dis(gen);
    double angolo = dis(gen);
    dato = std::make_pair(velocita, angolo);
}

std::pair<double, double> Vento::Misura(std::pair<double, double> valoreReale) {
    double velocita = valoreReale.first + offset();
    double angolo = valoreReale.second;
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
    std::uniform_real_distribution<> dis(valoreMin, valoreMax);
    //salvo il dato misurato assicurandomi che rispetti la precisione dello strumento
    return std::round(dato = dis(valoreReale)/ tolleranza) * tolleranza;
}


//--------------------Umidita--------------------
class Umidita : public Sensore {
private:
    double valoreMin;
    double valoreMax;
    std::pair<double,double> rangeOttimale;
    double tolleranza;
    double dato;
    enum distribuzione{};
public:
    Umidita(unsigned int id, std::string nome, distribuzione dist);
    ~Umidita();
    Umidita(const Umidita&);
    double getMin();
    double getMax();
    double getDato();
    double getTolleranza();
    bool outOfRange();
    std::pair<double,double> simulaMisura();
};

class TemPercepita : public Temperatura, public Umidita {
private:
public:
};