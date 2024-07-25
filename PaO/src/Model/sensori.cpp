#include "sensori.h"
#include "sensore.h"
#include "fotocellula.h"
#include "temperatura.h"
#include "umidita.h"
#include "vento.h"
#include "TemPercepita.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>


Sensori::Sensori() {}

Sensori::Sensori(const QJsonArray& json) {
    for (const auto& sensoriJson : json) {
        QJsonObject sensoriObj = sensoriJson.toObject();
        std::string tipo = sensoriObj["Tipo"].toString().toStdString();
        if (tipo == "Fotocellula") {
            Fotocellula* f = new Fotocellula(sensoriObj);
            aggiungi(f);
        } else if (tipo == "Vento") {
            Vento* v = new Vento(sensoriObj);
            aggiungi(v);
        } else if (tipo == "Temperatura") {
            Temperatura* t = new Temperatura(sensoriObj);
            aggiungi(t);
        } else if (tipo == "Umidita") {
            Umidita* u = new Umidita(sensoriObj);
            aggiungi(u);
        } else if (tipo == "TemPercepita") {
            TemPercepita* tp = new TemPercepita(sensoriObj);
            aggiungi(tp);
        }
    }
}

Sensori::~Sensori() {
    for (Sensore* s : sensori) {
        delete s;
    }
}

void Sensori::aggiungi(Sensore* s) {
    sensori.push_back(s);
}

void Sensori::rimuovi(unsigned int id) {
    for (auto it = sensori.begin(); it != sensori.end(); ++it) {
        if ((*it)->getID() == id) {
            delete *it;
            sensori.erase(it);
            it=sensori.end();
        }
    }
}

Sensore* Sensori::get(unsigned int id) const {
    for (Sensore* s : sensori) {
        if (s->getID() == id) {
            return s;
        }
    }
    return nullptr;
}

QJsonArray Sensori::salva() const {

    QJsonArray sensoriArray;
    for (Sensore* s : sensori) {
        sensoriArray.append(s->salva());
    }

    return sensoriArray;
}
