// inserire tutta la logica che gestisce i json
// trovare il modo per collegarli agli altri file
#include <QJsonObject>


QJsonObject Fotocellula::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Attivo"] = isAttivo();
    json["Soglia"] = getSoglia();
    json["Tolleranza"] = getTolleranza();
    return json;
}

QJsonObject Sensore::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(ID);
    json["Nome"] = QString::fromStdString(nome);
    return json;
}

QJsonObject Vento::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Offset"] = getOffset();
    json["MaxVelocita"] = getMaxVelocita();
    json["TolleranzaGoniometro"] = getTolleranzaGoniometro();
    json["TolleranzaAnemometro"] = getTolleranzaAnemometro();
    json["Dato"] = QJsonObject{
        {"Velocita", getDato().first},
        {"Angolo", getDato().second}
    };
    return json;
}

QJsonObject Temperatura::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Min"] = getMin();
    json["Max"] = getMax();
    json["ValoreIdeale"] = getValoreIdeale();
    json["Tolleranza"] = getTolleranza();
    json["Dato"] = getDato();
    return json;
}

QJsonObject Umidita::salva() const {
    QJsonObject json;
    json["ID"] = static_cast<int>(getID());
    json["Nome"] = QString::fromStdString(getNome());
    json["Min"] = getMin();
    json["Max"] = getMax();
    json["RangeOttimale"] = QJsonObject{
        {"Min", rangeOttimale.first},
        {"Max", rangeOttimale.second}
    };
    json["Tolleranza"] = getTolleranza();
    json["Dato"] = getDato();
    return json;
}
