#ifndef VENTO_H
#define VENTO_H

#include "Sensore.h"
#include <utility>

class Vento : public Sensore {
private:

    double tolleranzaGoniometro;
    double tolleranzaAnemometro;
    double offset;
    double valoreMaxVelocita;
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

    void setOffset(double offset);
    void simulaMisura() override;
    std::pair<double, double> Misura(std::pair<double, double> valoreReale);
    QJsonObject salva() const override;
};

#endif // VENTO_H
