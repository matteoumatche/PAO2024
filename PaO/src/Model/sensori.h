#ifndef SENSORI_H
#define SENSORI_H

#include <vector>
#include "Sensore.h"

class Sensori {
private:
    std::vector<Sensore*> sensori;
public:
    explicit Sensori();
    Sensori(const QJsonArray& );
    ~Sensori();
    void aggiungi(Sensore* );
    void rimuovi(unsigned int );
    Sensore* get(unsigned int ) const;
    QJsonArray salva() const;
};
#endif // SENSORI_H
