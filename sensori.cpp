#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <QJsonObject>
#include "math.h"




// ciò che riguarda la UI
namespace View {
    class UI {
    public:
        void prompt(std::string s) {
            std::cout << s;
        }

        int getInput() {
            int x;
            std::cin >> x;
            return x;
        }
    };
}

// ciò che riguarda il data storage
namespace Model {

class Errore {
private:
    std::string err;
public:
    Errore(std::string e): err(e){}
};

//--------------------Sensore--------------------
class Sensore {
private:
    unsigned int ID;
    std::string nome;
protected:
    Sensore(unsigned int id, std::string nome);
<<<<<<< HEAD
    Sensore(const QJsonObject& json);
    /*ho eliminato il distruttore e il costruttore di copia perchè vanno bene quelli standard*/

=======
public:
>>>>>>> d30b21c10b3d00fe69d6b38680a483f67437ecbe
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
<<<<<<< HEAD
    double soglia;
    double tolleranza;

=======
>>>>>>> d30b21c10b3d00fe69d6b38680a483f67437ecbe
public:
    Fotocellula(unsigned int id, std::string n, double s, double t);
    
    bool isAttivo() const;

    void simulaMisura() override;
    bool Misura(bool valoreReale);
};

Fotocellula::Fotocellula(unsigned int id, std::string nome, double s, doule t) : 
Sensore(id,nome), 
attivo(false), 
soglia(s), 
tolleranza(t) {}

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


//--------------------Vento--------------------
class Vento : public Sensore {
private:
    double valoreMaxVelocita;   //questo è const? Essendo valore massimo
    double tolleranzaGoniometro;
    double tolleranzaAnemometro;
    double offset;  //come è posizionato
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
<<<<<<< HEAD
    QJson save() const;
=======
>>>>>>> d30b21c10b3d00fe69d6b38680a483f67437ecbe
};

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

//costruttore standard(?)
Temperatura::Temperatura(unsigned int id, std::string nome) : 
    Sensore(id, nome), 
    valoreMin(-10), 
    valoreMax(100), 
    valoreIdeale(20), 
    tolleranza(0.1), 
    dato(0) {}

//costruttore a 6 parametri(?)
Temperatura::Temperatura(unsigned int id, std::string nome, double toll, double min, double max, double ideale) : 
    Sensore(id, nome),  tolleranza(toll>0 ? toll : 0.1), dato(0) {
       
        if(min >= zeroAssoluto)        valoreMin = std::round(min/ tolleranza) * tolleranza;
        else                           valoreMin = zeroAssoluto;

        valoreMax =  std::round(max/ tolleranza) * tolleranza;
        valoreIdeale =  std::round(ideale/ tolleranza) * tolleranza;
    }

double Temperatura::getMin() const {
    if(valoreMin<0)         throw Errore("Rischio ghiaccio");
    else                    return valoreMin;
}

double Temperatura::getMax() const {
    if(valoreMax>30)        throw Errore("Rischio bruciatura piante");
    else                    return valoreMax;
}

double Temperatura::getDato() const {
    if(dato<0 || dato>30)   throw Errore("Temperatura registrata fuori range di sicurezza");
    else                    return dato;
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
<<<<<<< HEAD
    

    std::ostream& operator<<(std::ostream& os) const;
=======
>>>>>>> d30b21c10b3d00fe69d6b38680a483f67437ecbe
};

//costruttore standard(?)
Umidita::Umidita(unsigned int id, std::string n) : 
    Sensore(id, n), 
    valoreMin(0), 
    valoreMax(30), 
    rangeOttimale(std::make_pair(5, 100)), 
    tolleranza(0.1), 
    dato(0) {
}

//costruttore a 6 parametri(?)
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
    if(valoreMin<0)         throw Errore("Ambiente troppo secco");
    else                    return valoreMin;
}

double Umidita::getMax() const {
    if(valoreMax>30)         throw Errore("Ambiente troppo umido");
    else                     return valoreMax;
}

double Umidita::getDato() const {
    if(dato<0 || dato>30)   throw Errore("Umidità registrata fuori range di sicurezza");
    else                    return dato;
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


//--------------------TemPercepita--------------------
class TemPercepita : public Sensore {
private:
    Umidita u;
    Temperatura t;
    double IndiceCalore;
public:
    TemPercepita(unsigned int id, std::string nome, Umidita u, Temperatura t);
    TemPercepita(Temperatura t);
    double getIndiceCalore() const;
    void simulaMisura();
    double Misura(double);
};

TemPercepita::TemPercepita(unsigned int id, std::string nome, Umidita u, Temperatura t) : Sensore(id,nome), u(u), t(t)  {
    if(t.getDato()>27)    
        IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    else                  
        IndiceCalore = t.getDato();
}

/*
TemPercepita::TemPercepita(Temperatura t) : t(t) , u(0, "umidita"){
    if(t.getDato()>27)   
     IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    else                 
     IndiceCalore = t.getDato();
}
*/

double TemPercepita::getIndiceCalore() const {
    if(IndiceCalore<0 || IndiceCalore>30)   throw Errore("Temperatura percepita registrata fuori range di sicurezza");
    else                                    return IndiceCalore;
}

void TemPercepita::simulaMisura() {
    u.simulaMisura();
    t.simulaMisura();
    IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
}

double TemPercepita::Misura(double valoreReale) {
    u.Misura((valoreReale>0 || valoreReale<30) ? valoreReale : throw Errore("Umidità misurata fuori range di sicurezza"));
    t.Misura((valoreReale>0 || valoreReale<30) ? valoreReale : throw Errore("Temperatura misurata fuori range di sicurezza"));
    IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    return IndiceCalore;
}

}

// ciò che riguarda la logica
namespace Controller {

}




int main() {
    Model::Fotocellula f(2, "fotocellula");
    Model::Vento v(3, "vento");
    Model::Temperatura t(4, "temperatura");
    Model::Umidita u(5, "umidita");
    
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