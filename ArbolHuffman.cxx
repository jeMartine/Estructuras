#include "ArbolHuffman.h"

ArbolHuffman::ArbolHuffman() : raiz(nullptr) {}

// Implementación de construirArbol
void ArbolHuffman::construirArbol(const string &texto)
{
    //el comparador es usado para organizar de menor a mayor en la cola de prioridad
    priority_queue<Nodo *, vector<Nodo *>, Comparador> pq;
    //si llega un texto vacio
    if (texto.empty())
    {
        return;
    }

    //recorre el texto completo y aumenta frecuencia de cada caracter
    for (int i = 0; i < texto.length(); ++i)
    {
        char ch = texto[i];
        frecuencias[ch]++;
    }
    
    //guarda en la cola de prioridad un nuevo nodo
    //recorre el mapa de frecuencias
    for (std::map<int, int>::iterator it = frecuencias.begin(); it != frecuencias.end(); ++it) {
    pq.push(new Nodo(it->first, it->second, nullptr, nullptr));
}

    // Manejar el caso especial de un solo carácter
    if (pq.size() == 1)
    {
        Nodo *solo = pq.top();
        raiz = new Nodo('\0', solo->getFreq(), solo, nullptr);
    }
    else
    {
        while (pq.size() != 1)
        {
            Nodo *izquierda = pq.top();
            pq.pop();
            Nodo *derecha = pq.top();
            pq.pop();
            int suma = izquierda->getFreq() + derecha->getFreq();
            pq.push(new Nodo('\0', suma, izquierda, derecha));
        }
        raiz = pq.top();
    }
}

// Implementación de codificar
void ArbolHuffman::codificar()
{
    if (!raiz)
    {
        return;
    }
    if (esHoja(raiz))
    {
        codigoHuffman[raiz->getAscii()] = "0"; // Caso especial para un solo nodo
    }
    else
    {
        codificar(raiz, "");
    }
}

// Implementación de codificar
void ArbolHuffman::codificar(Nodo *raiz, string str)
{
    if (raiz == nullptr)
    {
        return;
    }

    if (esHoja(raiz))
    {
        codigoHuffman[raiz->getAscii()] = (str != "") ? str : "1";
    }

    codificar(raiz->getIzquierda(), str + "0");
    codificar(raiz->getDerecha(), str + "1");
}

// Implementación de decodificar
void ArbolHuffman::decodificar(const string &strCodificada)
{

    // Abre un archivo de texto para escribir el texto decodificado
    ofstream archivo("Decodificado.txt");

    int indice = -1;
    while (indice < (int)strCodificada.size() - 1)
    {
        decodificar(raiz, indice, strCodificada, archivo);
    }
    archivo.close();
    cout << "Decodificado.txt creado" << endl;
}

// Implementación de decodificar (overload)
void ArbolHuffman::decodificar(Nodo *raiz, int &indice, const string &str, ofstream &archivo)
{
    if (raiz == nullptr)
    {
        return;
    }

    if (esHoja(raiz))
    {
        // cout << char(raiz->ascii);
        archivo << char(raiz->getAscii());
        return;
    }

    indice++;

    if (str[indice] == '0')
    {
        decodificar(raiz->getIzquierda(), indice, str, archivo);
    }
    else
    {
        decodificar(raiz->getDerecha(), indice, str, archivo);
    }
}

// Implementación de esHoja
bool ArbolHuffman::esHoja(Nodo *raiz)
{
    return raiz->getIzquierda() == nullptr && raiz->getDerecha() == nullptr;
}

// Implementación de guardarEnArchivoBinario
void ArbolHuffman::guardarEnArchivoBinario(const string &strCodificada, const string &nombreArchivo)
{
    // n
    int value = codigoHuffman.size();
    //tamaño del codigo como un entero de 16 bits en binario
    bitset<16> twoByteRepresentation(value);
    string binaryString = twoByteRepresentation.to_string();

    //escribir el archivo binario
    ofstream archivo(nombreArchivo, ios::binary);
    //se escirbe del archivo en un string de binarios
    archivo << binaryString;

    // ci y fi
    for (map<int, int>::iterator it = frecuencias.begin(); it != frecuencias.end(); ++it)
    {
        bitset<8> ascii(it->first);
        archivo << ascii.to_string();

        bitset<64> freq(it->second);
        archivo << freq.to_string();
    }

    // w
    int sum = 0;
    for (map<int, int>::iterator it = frecuencias.begin(); it != frecuencias.end(); ++it)
    {
        sum += it->second;
    }
    bitset<64> w(sum);
    archivo << w.to_string();

    // binary_code
    archivo << strCodificada;

    archivo.close();
}


// Implementación de reconstruirArbol
void ArbolHuffman::reconstruirArbol(const map<int, int> &frecuencias)
{
    priority_queue<Nodo *, vector<Nodo *>, Comparador> pq;

    for (map<int, int>::const_iterator it = frecuencias.begin(); it != frecuencias.end(); ++it)
    {
        pq.push(new Nodo(it->first, it->second, nullptr, nullptr));
    }

    while (pq.size() != 1)
    {
        Nodo *izquierda = pq.top();
        pq.pop();
        Nodo *derecha = pq.top();
        pq.pop();
        int suma = izquierda->getFreq() + derecha->getFreq();
        pq.push(new Nodo('\0', suma, izquierda, derecha));
    }

    raiz = pq.top();
}

std::string ArbolHuffman::getCodigohuffman(char ch)
{
    return codigoHuffman[ch];
}

