#ifndef CONTINENTE_H
#define CONTINENTE_H

#include <string>
#include <vector>
#include "Territorio.h" 
#include "Jugador.h"
#include "Ficha.h"

class Continente {
public:
    Continente(std::string nNombre);
    std::string obtenerNombre();
    void ocuparTerritorio(Ficha ficha, int nTerritorio, std::string nombreJugador); 
    void AddTerritorio( std::string nombre, int _id);
    int cantidadTerritorios();
    std::string getNombreTerritorio(int indice);
    bool territorioValido(std::string territorio);
    std::string reclamado(int indice);
    int getTerritoriosOcupados();
    int getFichasEnTerritorio(int indice);
    int getIdTerritorio(int indice);
    bool continenteOcupado(std::string nombreJugador);
    void eliminarFichaTerritorio(int terri);
    Territorio buscarId(int id);
    Territorio getTerritorio(int ind);

private:
    std::string nombre;
    std::vector<Territorio> territorios;
    int territoriosOcupados;
};

#endif // CONTINENTE_H
