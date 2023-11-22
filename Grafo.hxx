#ifndef GRAFO_HXX
#define GRAFO_HXX

#include "Grafo.h"

template <typename T>
void Grafo<T>::agregarNodo(const T &nodo)
{
    if (nodosMap.find(nodo) == nodosMap.end())
    {
        nodosMap[nodo] = nodos.size();
        nodos.push_back(nodo);

        // Añadir una nueva fila a la matriz de adyacencia con ceros
        matrizAdyacencia.push_back(vector<int>(nodos.size(), 0));

        // Actualizar todas las filas existentes añadiendo un nuevo elemento inicializado en 0
        for (int i = 0; i < matrizAdyacencia.size() - 1; i++)
        {
            matrizAdyacencia[i].push_back(0);
        }
    }
}

template <typename T>
void Grafo<T>::agregarArista(const T &origen, const T &destino, int peso)
{
    if (nodosMap.find(origen) != nodosMap.end() && nodosMap.find(destino) != nodosMap.end())
    {
        int indiceOrigen = nodosMap[origen];
        int indiceDestino = nodosMap[destino];
        matrizAdyacencia[indiceOrigen][indiceDestino] = peso;
    }
}

template <typename T>
void Grafo<T>::recorridoMasCorto(const T &inicio, const T &fin, map<int, string> &textCaminos)
{
    if (nodosMap.find(inicio) == nodosMap.end() || nodosMap.find(fin) == nodosMap.end())
    {
        cout << "Uno de los nodos no existe en el grafo." << endl;
        return; // Finaliza si alguno de los nodos no existe
    }

    int indiceInicio = nodosMap[inicio];
    int indiceFin = nodosMap[fin];
    vector<bool> visitado(nodos.size(), false);
    queue<int> cola;
    map<int, int> predecesores; // Para reconstruir el camino
    string aux = "";

    visitado[indiceInicio] = true;
    cola.push(indiceInicio);
    predecesores[indiceInicio] = -1; // Indicador de inicio del recorrido

    while (!cola.empty())
    {
        int nodoActual = cola.front();
        cola.pop();

        if (nodoActual == indiceFin)
        {
            break; // Hemos llegado al nodo final
        }

        for (int i = 0; i < nodos.size(); i++)
        {
            if (matrizAdyacencia[nodoActual][i] != 0 && !visitado[i])
            {
                visitado[i] = true;
                cola.push(i);
                predecesores[i] = nodoActual; // Guardar el predecesor
            }
        }
    }

    if (!visitado[indiceFin])
    {
        cout << "No hay camino entre " << inicio << " y " << fin << "." << endl;
        return; // No hay camino entre inicio y fin
    }

    // Reconstruir y mostrar el camino más corto junto con el precio de cada conexión
    // cout << "Camino mas corto de " << inicio << " a " << fin << ": ";
    aux += "\nDebes tomar el camino mas corto de <" + inicio + "> a <" + fin + ">: \n";

    vector<int> caminoInvertido;
    int actual = indiceFin;
    int nCamino = 0;

    while (actual != -1)
    {
        caminoInvertido.push_back(actual);
        actual = predecesores[actual];
    }

    int sumaTotal = 0;
    for (int i = caminoInvertido.size() - 1; i > 0; i--)
    {
        int desde = caminoInvertido[i];
        int hacia = caminoInvertido[i - 1];
        int precio = matrizAdyacencia[desde][hacia];

        // cout << nodos[desde] << " - " << precio << " -> ";
        aux += nodos[desde] + " - " + to_string(precio) + " -> ";
        nCamino++;
        sumaTotal += precio;
    }

    // cout << nodos[caminoInvertido[0]] << endl;
    aux += nodos[caminoInvertido[0]];
    // cout << "Debe conquistar " <<  sumaTotal << " unidades de ejercito." << endl;
    aux += "\nDebe conquistar " + to_string(sumaTotal) + " unidades de ejercito.\n";

    // clave: numero de caminos que hay
    // string: texto de salida
    textCaminos[nCamino] = aux;
}

template <typename T>
void Grafo<T>::recorridoEnAnchura(const T &inicio, vector<int> propios)
{
    // verificar que el nodo de inicio exista
    if (nodosMap.find(inicio) != nodosMap.end())
    {
        // indica el indice del nodo de desde donde empieezo
        int indiceInicio = nodosMap[inicio] + 1;
        // vector de visitados
        vector<bool> visitado(nodos.size(), false);
        // para el recorrido en anchura
        queue<int> cola;
        map<int, string> textCaminos; // almacenar la frecuencia y el texto de cada camino

        visitado[indiceInicio] = true;
        cola.push(indiceInicio);

        // se deben visitar todos los nodos
        while (!cola.empty())
        {
            int nodoActual = cola.front();
            cola.pop();

            // Iterar sobre propios para buscar coincidencias
            for (int i = 0; i < propios.size(); ++i)
            {
                int indice = propios[i];
                // std::cout<<indice<<" : "<<nodoActual<<" : "<<indiceInicio<<endl;
                if (indice == nodoActual && nodoActual != indiceInicio)
                {
                    // cout<<"inicio desde: "<<nodos[nodoActual-1]<<" -> "<<nodos[indiceInicio-1]<<endl;
                    recorridoMasCorto(nodos[nodoActual - 1], nodos[indiceInicio - 1], textCaminos);
                }
            }

            for (int i = 0; i < nodos.size(); i++)
            {
                if (matrizAdyacencia[nodoActual][i] != 0 && !visitado[i])
                {
                    visitado[i] = true;
                    cola.push(i);
                }
            }
        }

        //mostrar la menor ruta
        if (!textCaminos.empty())
        {
            map<int, string>::iterator minElement = min_element(
                textCaminos.begin(), textCaminos.end(),
                [](const pair<const int, string> &a, const pair<const int, string> &b)
                {
                    return a.first < b.first;
                });

            cout << minElement->first << ": " << minElement->second << endl;
        }
        else
        {
            cout << "El territorio ingresado no existe.\n";
        }
    }
}

template <typename T>
int Grafo<T>::FloydWarshall(const T &origen, const T &destino, vector<T> &caminoMinimo)
{
    if (nodosMap.find(origen) == nodosMap.end() || nodosMap.find(destino) == nodosMap.end())
    {
        return INFINITO;
    }

    int n = nodos.size();
    vector<vector<int>> dist(n, vector<int>(n, INFINITO));
    vector<vector<int>> next(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
        for (int j = 0; j < n; j++)
        {
            if (matrizAdyacencia[i][j] != 0)
            {
                dist[i][j] = matrizAdyacencia[i][j];
                next[i][j] = j;
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] < INFINITO && dist[k][j] < INFINITO && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    int u = nodosMap[origen];
    int v = nodosMap[destino];
    if (next[u][v] == -1)
    {
        return INFINITO;
    }

    int sumaTotal = 0;
    while (u != v)
    {
        caminoMinimo.push_back(nodos[u]);
        sumaTotal += dist[u][v];
        u = next[u][v];
    }
    caminoMinimo.push_back(nodos[v]);

    return sumaTotal;
}

#endif // GRAFO_HXX