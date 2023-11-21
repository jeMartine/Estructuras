#ifndef RISK_H
#define RISK_H

#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <cstdlib> // Necesario para srand y rand
#include <time.h>
#include "Jugador.h" 
#include "Carta.h" 
#include "Continente.h" 
#include "Ficha.h"

class Risk {
public:
    Risk();
    int LanzarDado();
    void iniciarPartida();
    bool estadoPartida();
    void asignarGanador();
    void crearContinente();
    void agregarCartas(std::string territorio, std::string tropa);
    std::string infoContinente();
    void CrearJugador(std::string nombre, int qJugadores);
    std::string colorJugador();
    int qUnidades(int qJugadores);

    std::string infoJug();
    std::string infoTerritorios(std::string nameContinente);
    bool estadoTerritorio(std::string nameContinente, std::string nameTerritorio);
    void turnoJugado();
    std::string getNameJugadorEnTurno();
    std::string getColorJugadorEnTurno();
    bool moverFichasJugador(int qFichas, std::string continente, std::string territorio);
    int indiceContinente(std::string continente);
    int indiceTerritorio(int iContinente, std::string territorio);
    bool territoriosLibres();

    std::string territoriosJugador();
    int getFichasJugadorEnTurno();
    std::string buscarContinenteTerritorio(std::string territorio);
    bool territorioJugador(std::string continente, std::string territorio);

    bool estadoGanador();
    bool esTurnoJugador(std::string nombreIngresado);
    bool jugadorExiste(std::string nombreIngresado);
    
    void turnosEnCero();

    std::string guardarPartida();
    std::string territoriosJugadorArch(int iJugador);

    void sumarPaisJugador();
    //2da entrega
    void nuevasTropasTerritorio();
    void nuevasTropasContiente();
    Carta getCarta();
    int numeroAleatorio(int minimo, int maximo);
    void agregarTerritorio(int continente, std::string nombreTerritorio, int id);
   // void agregarVecinoTerritorio(int continente, int territorio, std::string nombreVecino);

   // void mostrarVecinosTerritorio(int conti, int terri);
    std::string buscarFichasTerritorio(std::string terri);
    //bool validarDefensa(int indContiente, int indterritorio, std::string territorio);
    int fichasTerritorio(std::string terri);
    bool deleteFichaTerritorio(std::string terri);
    bool conquistarTerritorio(std::string terri, std::string nombreJugador);
    std::string buscarPropietario(std::string terri);
    void agregarCarta(Carta cartaAux);
    std::string cartasDeJugador(int indJugador);
    std::string espacioPorRaya(std::string cadena);
    bool poblarTerritorio(std::string terri, int qFichas, std::string nombreJugador, std::string colorJug);
    std::string getColorJugador(int indice);
    std::string getNombreJugador(int indice);
    void agregarCartaJugador(std::string terri, std::string tropa, int indJugador);

private:
    std::vector<Jugador> jugadores;
    std::vector<Carta> cartas;
    std::vector<Continente> continentes;
    bool Partida;
    bool Ganador;
    int turnoActual;
    int Totalturnos;
};

#endif // RISK_H