#ifndef COMPARADOR_H
#define COMPARADOR_H

#include "Nodo.h"

class Comparador {
public:
    bool operator()(Nodo* a, Nodo* b);
};

#endif // COMPARADOR_H
