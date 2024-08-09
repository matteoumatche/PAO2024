#include "tempercepita.h"
#include <QJsonDocument>
namespace Model{

TemPercepita::TemPercepita(unsigned int id, std::string nome, Umidita um, Temperatura te) : Sensore(id,nome), u(um), t(te)  {
    if(t.getDato()>27)
        IndiceCalore = 13.12 + 0.6215 * te.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    else
        IndiceCalore = t.getDato();
}

TemPercepita::TemPercepita(unsigned int id, std::string nome) : Sensore(id, nome), u(1, "ok"), t(11, "ok") {}

TemPercepita::TemPercepita(const QJsonObject& json) :
    Sensore(json),
    u(json["Umidita"].toObject()),
    t(json["Temperatura"].toObject()),
    IndiceCalore( json["IndiceCalore"].toInt()) {}


double TemPercepita::getIndiceCalore() const {
    return IndiceCalore;
}

void TemPercepita::simulaMisura() {
    u.simulaMisura();
    t.simulaMisura();
    IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
}

double TemPercepita::Misura(double valoreReale) {
    u.Misura(valoreReale);
    t.Misura(valoreReale);
    IndiceCalore = 13.12 + 0.6215 * t.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    return IndiceCalore;
}

std::map<std::string, std::string> TemPercepita::getInfo() const {
    std::map<std::string, std::string> info;

    // Uniamo le informazioni dalla classe base (Sensore)
    auto baseInfo = Sensore::getInfo();
    info.insert(baseInfo.begin(), baseInfo.end());

    // Aggiungiamo le informazioni specifiche per TemPercepita
    info["Tipo"] = "TemPercepita";
    info["IndiceCalore"] = std::to_string(IndiceCalore);

    // Otteniamo le informazioni da Umidita e Temperatura
    auto umiditaInfo = u.getInfo();
    auto temperaturaInfo = t.getInfo();

    // Convertiamo le mappe in QJsonObject manualmente
    QJsonObject umiditaJson;
    for (const auto& pair : umiditaInfo) {
        umiditaJson[QString::fromStdString(pair.first)] = QString::fromStdString(pair.second);
    }

    QJsonObject temperaturaJson;
    for (const auto& pair : temperaturaInfo) {
        temperaturaJson[QString::fromStdString(pair.first)] = QString::fromStdString(pair.second);
    }

    // Convertiamo i QJsonObject in stringhe JSON compatte
    QJsonDocument umiditaDoc(umiditaJson);
    QJsonDocument temperaturaDoc(temperaturaJson);

    info["Umidita"] = umiditaDoc.toJson(QJsonDocument::Compact).toStdString();
    info["Temperatura"] = temperaturaDoc.toJson(QJsonDocument::Compact).toStdString();

    return info;
}

}
