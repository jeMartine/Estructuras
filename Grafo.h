#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>
using namespace std;

const int INFINITO = 1000000;


template <typename T>
class Grafo {
public:
    void agregarNodo(const T& nodo);
    void agregarArista(const T& origen, const T& destino, int peso);
    void recorridoMasCorto(const T& inicio, const T& fin);
    void recorridoEnAnchura(const T& inicio, vector<int> propios);
    int FloydWarshall(const T& origen, const T& destino, vector<T>& caminoMinimo);
 

private:
    map<T, int> nodosMap;
    vector<T> nodos;
    vector<vector<int>> matrizAdyacencia;
};

#include "Grafo.hxx"

#endif // GRAFO_H
