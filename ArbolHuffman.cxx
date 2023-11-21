#include "ArbolHuffman.h"

ArbolHuffman::ArbolHuffman() : raiz(nullptr) {}

// Implementación de construirArbol
void ArbolHuffman::construirArbol(const string& texto) {
    if (texto.empty()) {
        return;
    }

    for (char ch : texto) {
        frecuencias[ch]++;
    }

    priority_queue<Nodo*, vector<Nodo*>, Comparador> pq;
    for (auto& par : frecuencias) {
        pq.push(new Nodo(par.first, par.second, nullptr, nullptr));
    }

    // Manejar el caso especial de un solo carácter
    if (pq.size() == 1) {
        Nodo* solo = pq.top();
        raiz = new Nodo('\0', solo->freq, solo, nullptr);
    } else {
        while (pq.size() != 1) {
            Nodo* izquierda = pq.top(); pq.pop();
            Nodo* derecha = pq.top(); pq.pop();
            int suma = izquierda->freq + derecha->freq;
            pq.push(new Nodo('\0', suma, izquierda, derecha));
        }
        raiz = pq.top();
    }

}


// Implementación de codificar
void ArbolHuffman::codificar() {
    if (!raiz) {
        return;
    }
    if (esHoja(raiz)) {
        codigoHuffman[raiz->ascii] = "0"; // Caso especial para un solo nodo
    } else {
        codificar(raiz, "");
    }
}


// Implementación de codificar (overload)
void ArbolHuffman::codificar(Nodo* raiz, string str) {
    if (raiz == nullptr) {
        return;
    }

    if (esHoja(raiz)) {
        codigoHuffman[raiz->ascii] = (str != "") ? str : "1";
    }

    codificar(raiz->izquierda, str + "0");
    codificar(raiz->derecha, str + "1");
}


// Implementación de decodificar
void ArbolHuffman::decodificar(const string& strCodificada) {
    
    //Abre un archivo de texto para escribir el texto decodificado
    ofstream archivo("Decodificado.txt");
  
    
    int indice = -1;
    while (indice < (int)strCodificada.size() - 1) {
        decodificar(raiz, indice, strCodificada, archivo);
    }
    archivo.close();
    cout << "Decodificado.txt creado" << endl;
}


// Implementación de decodificar (overload)
void ArbolHuffman::decodificar(Nodo* raiz, int& indice, const string& str, ofstream& archivo) {
    if (raiz == nullptr) {
        return;
    }


    if (esHoja(raiz)) {
        //cout << char(raiz->ascii);
        archivo << char(raiz->ascii);
        return;
    }

    indice++;

    if (str[indice] == '0') {
        decodificar(raiz->izquierda, indice, str, archivo);
    } else {
        decodificar(raiz->derecha, indice, str, archivo);
    }
}


// Implementación de esHoja
bool ArbolHuffman::esHoja(Nodo* raiz) {
    return raiz->izquierda == nullptr && raiz->derecha == nullptr;
}


// Implementación de guardarEnArchivoBinario
void ArbolHuffman::guardarEnArchivoBinario(const string& strCodificada, const string& nombreArchivo) {
    
    //n
    int value = codigoHuffman.size();
    bitset<16> twoByteRepresentation(value);
    string binaryString = twoByteRepresentation.to_string();

    ofstream archivo(nombreArchivo, ios::binary);
    archivo << binaryString;

    //ci y fi

     
    for (auto& par : frecuencias) {
        bitset<8> ascii(par.first);
        archivo << ascii.to_string();

        bitset<64> freq(par.second);
        archivo << freq.to_string();
    }
    //w
    int sum = 0;
    for (auto& par : frecuencias) {
        sum += par.second;
    }
    bitset<64> w(sum);
    archivo << w.to_string();

    //binary_code
    archivo << strCodificada;

    archivo.close();

}


// Implementación de reconstruirArbol
void ArbolHuffman::reconstruirArbol(const map<int, int>& frecuencias) {
    priority_queue<Nodo*, vector<Nodo*>, Comparador> pq;
    for (auto& par : frecuencias) {
        pq.push(new Nodo(par.first, par.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        Nodo* izquierda = pq.top(); pq.pop();
        Nodo* derecha = pq.top(); pq.pop();
        int suma = izquierda->freq + derecha->freq;
        pq.push(new Nodo('\0', suma, izquierda, derecha));
    }
    raiz = pq.top();
}



