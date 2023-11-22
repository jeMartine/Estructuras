#include "Nodo.h"

Nodo::Nodo(int ascii, int freq, Nodo* izquierda, Nodo* derecha) {
    this->ascii = ascii;
    this->freq = freq;
    this->izquierda = izquierda;
    this->derecha = derecha;
}

void Nodo::addFreq(int freq){
    this->freq = freq;
}

int Nodo::getFreq(){
    return freq;
}

int Nodo::getAscii(){
    return ascii;
}

Nodo* Nodo::getIzquierda(){
    return izquierda;
}

Nodo* Nodo::getDerecha(){
    return derecha;
}
