#include "sensore.h"
#include<string>

namespace Model{

Sensore::Sensore(unsigned int id, std::string n) : ID(id), nome(n) {}

Sensore::Sensore(const QJsonObject& json) : nome(json["Nome"].toString().toStdString()) {

    QString idString = json["ID"].toString();
    bool ok;
    int id = idString.toInt(&ok); // Utilizza QString::toInt per la conversione
    if (ok) {
        ID = static_cast<unsigned int>(id);
        qDebug() << "ID successfully converted from JSON:" << ID;
    } else {
        qDebug() << "Failed to convert ID from string to int. Setting ID to 0.";
        ID = 0; // Imposta un valore predefinito se la conversione fallisce
    }
}

std::string Sensore::getNome() const {
    return nome;
}

unsigned int Sensore::getID() const {
    return ID;
}

void Sensore::setNome(std::string n) {
    nome = n;
}

std::map<std::string, std::string> Sensore::getInfo() const {
    std::map<std::string, std::string> info;
    info["ID"] = std::to_string(ID);
    info["Nome"] = nome;
    return info;
}

}
