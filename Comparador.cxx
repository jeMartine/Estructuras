#include "Comparador.h"

bool Comparador::operator()(Nodo* a, Nodo* b) {
    return a->freq > b->freq;
}
