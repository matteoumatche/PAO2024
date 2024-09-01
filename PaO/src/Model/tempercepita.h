#ifndef TEMPERCIPITA_H
#define TEMPERCIPITA_H

#include "temperatura.h"
#include "umidita.h"

namespace Model{

class TemPercepita : public Sensore {
private:
    Umidita u;
    Temperatura t;
    double IndiceCalore;

public:
    TemPercepita(unsigned int, std::string, Umidita, Temperatura);
    TemPercepita(unsigned int id, std::string nome);
    TemPercepita(const QJsonObject&);

    double getIndiceCalore() const;
    std::map<std::string, std::string> getInfo() const override;

    void simulaMisura() override;
    double Misura(double);

    virtual TemPercepita* clone() const override;
};

}

#endif
