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
    //Ficha GetFicha( std::string jugador);
    bool ChekFicha( std::string jugador);
    void setReclamar( std::string jugador);
    int ContarFichas( std::string jugador);
    int GetQFichas();
    std::string getNombre();
    std::string getReclamado();

private:
    std::string nombre;
    std::vector<std::string> territoriosVecinos;
    std::vector<Ficha> fichas;
    std::string reclamado;
    int unidades;
    int id;
};

#endif // TERRITORIO_H
