#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "Comparador.h"
#include "Nodo.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include <queue>

using namespace std;


class ArbolHuffman {
public:
    Nodo* raiz;
    map<int, string> codigoHuffman;
    map<int, int> frecuencias;

    ArbolHuffman();
    void construirArbol(const string& texto);
    void codificar();
    void decodificar(const string& strCodificada);
    void guardarEnArchivoBinario(const string& strCodificada, const string& nombreArchivo);
    void reconstruirArbol(const map<int, int>& frecuencias);

private:
    void codificar(Nodo* raiz, string str);
    void decodificar(Nodo* raiz, int& indice, const string& str, ofstream& archivo);
    static bool esHoja(Nodo* raiz);
};

#endif // ARBOLHUFFMAN_H
