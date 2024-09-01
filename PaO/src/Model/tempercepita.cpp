#include "tempercepita.h"

#include <QJsonDocument>

namespace Model{

TemPercepita::TemPercepita(unsigned int id, std::string nome, Umidita um, Temperatura te) : Sensore(id,nome), u(um), t(te)  {
    if(t.getDato()>27)
        IndiceCalore = 13.12 + 0.6215 * te.getDato() - 11.37 * pow(u.getDato(), 0.16) + 0.3965 * t.getDato() * pow(u.getDato(), 0.16);
    else
        IndiceCalore = t.getDato();
}

TemPercepita::TemPercepita(unsigned int id, std::string nome) : Sensore(id, nome), u(1, "umidità"), t(1, "temperatura") {}

TemPercepita::TemPercepita(const QJsonObject& json) :
    Sensore(json),
    IndiceCalore( json["Indice Calore"].toInt()) {
    auto stringToDouble = [](const QString& str) -> double {
        bool ok;
        double value = str.toDouble(&ok);
        return ok ? value : 0.0;
    };

    auto handleError = [](const QString& message) {
        qDebug() << message;
    };

    if (json.contains("Umidità") && json["Umidità"].isString()) {
        QString umiditaJsonString = json["Umidità"].toString();
        QJsonDocument umiditaDoc = QJsonDocument::fromJson(umiditaJsonString.toUtf8());
        if (!umiditaDoc.isNull() && umiditaDoc.isObject()) {
            QJsonObject umiditaObj = umiditaDoc.object();
            u = Model::Umidita(umiditaObj);
        } else {
            handleError("Warning: Invalid 'Umidità' JSON string");
        }
    } else {
        handleError("Warning: Missing or incorrect 'Umidità' in JSON");
    }

    if (json.contains("Temperatura") && json["Temperatura"].isString()) {
        QString temperaturaJsonString = json["Temperatura"].toString();
        QJsonDocument temperaturaDoc = QJsonDocument::fromJson(temperaturaJsonString.toUtf8());
        if (!temperaturaDoc.isNull() && temperaturaDoc.isObject()) {
            QJsonObject temperaturaObj = temperaturaDoc.object();
            t = Model::Temperatura(temperaturaObj);
        } else {
            handleError("Warning: Invalid 'Temperatura' JSON string");
            t = Model::Temperatura(QJsonObject());
        }
    } else {
        handleError("Warning: Missing or incorrect 'Temperatura' in JSON");
        t = Model::Temperatura(QJsonObject());
    }

    if (json.contains("Indice Calore")) {
        if (json["Indice Calore"].isDouble()) {
            IndiceCalore = json["Indice Calore"].toDouble();
        } else if (json["Indice Calore"].isString()) {
            IndiceCalore = stringToDouble(json["Indice Calore"].toString());
        } else {
            handleError("Warning: 'Indice Calore' is of incorrect type in JSON");
            IndiceCalore = 0.0;
        }
    } else {
        handleError("Warning: Missing 'IndiceCalore' in JSON");
        IndiceCalore = 0.0;
    }
}

double TemPercepita::getIndiceCalore() const {
    return IndiceCalore;
}

void TemPercepita::simulaMisura() {
    u.Umidita::simulaMisura();
    t.Temperatura::simulaMisura();
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

    auto baseInfo = Sensore::getInfo();
    info.insert(baseInfo.begin(), baseInfo.end());

    info["Tipo"] = "Temp. Percepita";
    info["Indice Calore"] = std::to_string(IndiceCalore);

    auto umiditaInfo = u.getInfo();
    if (umiditaInfo.find("Dato") != umiditaInfo.end()) {
        info["Umidità"] = umiditaInfo["Dato"];
    }

    auto temperaturaInfo = t.getInfo();
    if (temperaturaInfo.find("Dato") != temperaturaInfo.end()) {
        info["Temperatura"] = temperaturaInfo["Dato"];
    }

    return info;
}

TemPercepita* TemPercepita::clone() const {
    return new TemPercepita(*this);
}

}
