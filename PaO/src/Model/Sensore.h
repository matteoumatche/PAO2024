#ifndef SENSORE_H
#define SENSORE_H

#include <map>
#include <string>
#include <QJsonObject>

namespace Model{

class Sensore {
private:
    unsigned int ID;
    std::string nome;

public:
    Sensore(unsigned int id, std::string nome);
    Sensore(const QJsonObject& json);
    std::string getNome() const;
    unsigned int getID() const;
    void setNome(std::string n);
    void setID(unsigned int id);
    virtual std::map<std::string, std::string> getInfo() const;

    virtual void simulaMisura()=0;

    virtual Sensore* clone() const = 0;

    virtual ~Sensore(){};
};

}

#endif
