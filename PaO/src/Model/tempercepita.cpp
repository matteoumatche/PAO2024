#include "TemPercepita.h"

TemPercepita::TemPercepita(unsigned int id, std::string nome, Umidita um, Temperatura te) : Sensore(id,nome), u(um), t(te)  {
    if(t.getDato()>27)
        IndiceCalore = 13.12 + 0.6215 * te.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    else
        IndiceCalore = t.getDato();
}



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

QJsonObject TemPercepita::salva() const {
    QJsonObject json = Sensore::salva();
    json["Tipo"] = "TemPercepita";
    json["Umidita"] = u.salva();
    json["Temperatura"] = t.salva();
    json["IndiceCalore"] = getIndiceCalore();
    return json;
}
