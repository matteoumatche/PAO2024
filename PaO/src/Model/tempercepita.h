#ifndef TEMPERCIPITA_H
#define TEMPERCIPITA_H

#include "Temperatura.h"
#include "Umidita.h"

class TemPercepita : public Sensore {
private:
    Umidita u;
    Temperatura t;
    double IndiceCalore;
public:
    TemPercepita(unsigned int, std::string, Umidita, Temperatura );
    TemPercepita(const QJsonObject&);
    double getIndiceCalore() const;
    void simulaMisura() override;
    double Misura(double);
    QJsonObject salva() const override;
};

#endif // TEMPERCIPITA_H
