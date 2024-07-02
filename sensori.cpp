#include <iostream>
using namespace std;

class Sensore {
private:
    unsigned int ID;
    std::string nome;
    enum distribuzione{};
    void simulaMisura();
public:
    Sensore(unsigned int id, std::string nome, distribuzione dist);
    ~Sensore();
    Sensore(const Sensore&);
    std::string getNome() const;
    unsigned int getID() const;
    void setNome();
};

class Fotocellula : public Sensore {
private:
    bool attivo;
    bool setValoreRandom;
    double tempoRisposta;
    enum distribuzione{};
public:
    Fotocellula(unsigned int id, std::string nome, distribuzione dist);
    ~Fotocellula();
    Fotocellula(const Fotocellula&);
    bool isAttivo();
};

class NDVI : public Sensore {
private:
    bool attivo;
    bool setValoreRandom;
    double tempoRisposta;
    enum distribuzione{};
public:
    NDVI(unsigned int id, std::string nome, distribuzione dist);
    ~NDVI();
    NDVI(const NDVI&);
    bool isAttivo;
};

class Vento : public Sensore {
private:
    double valoreMaxVelocita;
    double tolleranzaGoniometro;
    double tolleranzaAnemometro;
    enum distribuzione{};
public:
    Vento(unsigned int id, std::string nome, distribuzione dist);
    ~Vento();
    Vento(const Vento&);
    double offset();
    void setMaxVelocita();
    double getMaxVelocita();
    std::pair<double,double> getDato();
    double getTolleranza();
    std::pair<double,double> simulaMisura();
};

class Temperatura : public Sensore {
private:
    double valoreMin;
    double valoreMax;
    const double valoreIdeale;
    double tolleranza;
    double dato;
    double zeroAssoluto = 0;
    enum distribuzione{};
public:
    Temperatura(unsigned int id, std::string nome, distribuzione dist);
    ~Temperatura();
    Temperatura(const Temperatura&);
    double getMin();
    double getMax();
    double getDato();
    double getTolleranza();
    bool isCold();
    bool isHot();
    double setValoreRandom();
    std::pair<double,double> simulaMisura();
};

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