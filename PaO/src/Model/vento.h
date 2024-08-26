#ifndef VENTO_H
#define VENTO_H

#include "sensore.h"

namespace Model{

class Vento : public Sensore {
private:

    double offset;
    double valoreMaxVelocita;
    double tolleranzaGoniometro;
    double tolleranzaAnemometro;
    std::pair<double, double> dato;

    double limitaAngolo(double x) const;

public:
    Vento(unsigned int , std::string , double );
    Vento(unsigned int , std::string , double o=0, double max=30, double tollG=0.1, double tollA=0.5);
    Vento(const QJsonObject& );

    double getMaxVelocita() const;
    double getOffset() const;
    double getTolleranzaGoniometro() const;
    double getTolleranzaAnemometro() const;
    std::pair<double, double> getDato() const;
    std::map<std::string, std::string> getInfo() const override;

    void setOffset(double offset);
    void setTolleranzaGoniometro(double tolleranzaGoniometro);
    void setTolleranzaAnemometro(double tolleranzaAnemometro);

    void simulaMisura() override;
    std::pair<double, double> Misura(std::pair<double, double> valoreReale);

    virtual Vento* clone() const override;
};

}

#endif
