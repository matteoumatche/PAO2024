#ifndef UMIDITA_H
#define UMIDITA_H
#include <map>
#include "Sensore.h"

class Umidita : public Sensore {
private:
    double tolleranza;
    double dato;

public:
    Umidita(unsigned int , std::string , double toll = 0.5);
    Umidita(const QJsonObject& );

    double getTolleranza() const;
    double getDato() const;
    std::map<std::string, std::string> getInfo() const;

    void simulaMisura() override;
    double Misura(double valoreReale);
};

#endif // UMIDITA_H
