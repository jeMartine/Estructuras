#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "Ficha.h" 
#include "Carta.h"
#include "Territorio.h"

class Jugador {
public:
    Jugador(std::string nombre, std::string nColor);
    std::string obtenerColor() ;
    std::string obtenerNombreJugador() ;
    void agregarCarta(Carta carta); 
    void agregarFicha(Ficha ficha); 
    Ficha moverFicha();
    std::vector<Ficha> obtenerFichas() ;
    int obeterTotalFichas();
    void sumarTerritorio();
    int getQterritorios();
    std::vector<Carta> getCartas();
   private:
    std::string color;
    std::vector<Carta> cartas;
    std::vector<Ficha> fichas;
    std::string nombreJugador;    
    int qTerritorios;
};

#endif // JUGADOR_H
