#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <string>
#include <vector>
#include "Ficha.h" 

class Territorio {
public:
    Territorio( std::string nuevoNombre, int _id);

    void addFicha(Ficha ficha);
    void deleteFicha();
    int getId();
    void setReclamar( std::string jugador);
    int GetQFichas();
    std::string getNombre();
    std::string getReclamado();

private:
    std::string nombre;
    std::vector<Ficha> fichas;
    std::string reclamado;
    int id;
};

#endif // TERRITORIO_H
