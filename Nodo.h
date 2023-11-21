#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    int ascii;
    int freq;
    Nodo *izquierda, *derecha;

    Nodo(int ascii, int freq, Nodo* izquierda, Nodo* derecha);
};

#endif // NODO_H
