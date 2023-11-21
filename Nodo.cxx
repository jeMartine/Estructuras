#include "Nodo.h"

Nodo::Nodo(int ascii, int freq, Nodo* izquierda, Nodo* derecha) {
    this->ascii = ascii;
    this->freq = freq;
    this->izquierda = izquierda;
    this->derecha = derecha;
}
