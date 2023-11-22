#include "Comparador.h"

bool Comparador::operator()(Nodo* a, Nodo* b) {
    return a->getFreq() > b->getFreq();
}
