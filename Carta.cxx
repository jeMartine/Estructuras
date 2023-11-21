#include "Carta.h"

Carta::Carta(std::string pais, std::string _tropa)
{
    territorio = pais;
    tropa = _tropa;
}

std::string Carta::getTerritorio()
{
    return territorio;
}
std::string Carta::getTropa()
{
    return tropa;
}