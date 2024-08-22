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
    IndiceCalore( json["IndiceCalore"].toInt()) {
    // Helper function to convert QString to double with error handling
    auto stringToDouble = [](const QString& str) -> double {
        bool ok;
        double value = str.toDouble(&ok);
        return ok ? value : 0.0; // Return 0.0 if conversion fails
    };

    // Helper function to handle errors
    auto handleError = [](const QString& message) {
        qDebug() << message;
    };

     //Check and initialize "Umidita"
    if (json.contains("Umidita") && json["Umidita"].isString()) {
        QString umiditaJsonString = json["Umidita"].toString();
        QJsonDocument umiditaDoc = QJsonDocument::fromJson(umiditaJsonString.toUtf8());
        if (!umiditaDoc.isNull() && umiditaDoc.isObject()) {
            QJsonObject umiditaObj = umiditaDoc.object();
            u = Model::Umidita(umiditaObj); // Assuming Umidita has a constructor accepting QJsonObject
        } else {
            handleError("Warning: Invalid 'Umidita' JSON string");
            u = Model::Umidita(QJsonObject()); // Default constructor
        }
    } else {
        handleError("Warning: Missing or incorrect 'Umidita' in JSON");
        u = Model::Umidita(QJsonObject()); // Default constructor
    }

    // Check and initialize "Temperatura"
    if (json.contains("Temperatura") && json["Temperatura"].isString()) {
        QString temperaturaJsonString = json["Temperatura"].toString();
        QJsonDocument temperaturaDoc = QJsonDocument::fromJson(temperaturaJsonString.toUtf8());
        if (!temperaturaDoc.isNull() && temperaturaDoc.isObject()) {
            QJsonObject temperaturaObj = temperaturaDoc.object();
            t = Model::Temperatura(temperaturaObj); // Assuming Temperatura has a constructor accepting QJsonObject
        } else {
            handleError("Warning: Invalid 'Temperatura' JSON string");
            t = Model::Temperatura(QJsonObject()); // Default constructor
        }
    } else {
        handleError("Warning: Missing or incorrect 'Temperatura' in JSON");
        t = Model::Temperatura(QJsonObject()); // Default constructor
    }

    // Check and convert "IndiceCalore"
    if (json.contains("IndiceCalore")) {
        if (json["IndiceCalore"].isDouble()) {
            IndiceCalore = json["IndiceCalore"].toDouble();
        } else if (json["IndiceCalore"].isString()) {
            IndiceCalore = stringToDouble(json["IndiceCalore"].toString());
        } else {
            handleError("Warning: 'IndiceCalore' is of incorrect type in JSON");
            IndiceCalore = 0.0; // Default value
        }
    } else {
        handleError("Warning: Missing 'IndiceCalore' in JSON");
        IndiceCalore = 0.0; // Default value
    }
}

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

TemPercepita* TemPercepita::clone() const {
    // Supponendo che tu abbia un costruttore di copia
    return new TemPercepita(*this);
}

}
