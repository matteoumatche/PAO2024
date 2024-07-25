#ifndef SENSORE_H
#define SENSORE_H

#include <string>
#include <QJsonObject>

class Sensore {
private:
    unsigned int ID;
    std::string nome;
public:
    Sensore(unsigned int id, std::string nome);
    Sensore(const QJsonObject& json);
    virtual ~Sensore(){};
    std::string getNome() const;
    unsigned int getID() const;
    void setNome(std::string n);
    virtual QJsonObject salva() const;

    virtual void simulaMisura()=0;
};

#endif // SENSORE_H
