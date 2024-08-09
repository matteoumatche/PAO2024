#ifndef TEMPERCIPITA_H
#define TEMPERCIPITA_H

#include <map>
#include "src/Model/Temperatura.h"
#include "src/Model/Umidita.h"

namespace Model{

class TemPercepita : public Sensore {
private:
    Umidita u;
    Temperatura t;
    double IndiceCalore;
public:
    TemPercepita(unsigned int, std::string, Umidita=0, Temperatura=0);
    TemPercepita(const QJsonObject&);
    double getIndiceCalore() const;
    std::map<std::string, std::string> getInfo() const;
    void simulaMisura() override;
    double Misura(double);
};

}

#endif // TEMPERCIPITA_H
