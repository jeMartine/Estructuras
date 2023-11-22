#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    void addFreq(int freq);
    int getFreq();
    int getAscii();
    Nodo* getIzquierda();
    Nodo* getDerecha();

    Nodo(int ascii, int freq, Nodo* izquierda, Nodo* derecha);
private:
    int ascii;
    int freq;
    Nodo *izquierda;
    Nodo *derecha;
};

#endif // NODO_H
