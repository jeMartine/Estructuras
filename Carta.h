#ifndef CARTA_H
#define CARTA_H

#include <string>

class Carta {
public:
    Carta(std::string pais, std::string _tropa);
    std::string getTerritorio();
    std::string getTropa();

private:
    std::string territorio;
    std::string tropa;
};

#endif // CARTA_H
