#include "Jugador.h"
// constructor
Jugador::Jugador(std::string nombre, std::string nColor)
{
  nombreJugador = nombre;
  color = nColor;
  qTerritorios=0;
}
// get color
std::string Jugador::obtenerColor()
{
  return color;
}

// get Nombre del jugador
std::string Jugador::obtenerNombreJugador()
{
  return nombreJugador;
}

// agregar la carta
void Jugador::agregarCarta(Carta carta)
{
  cartas.push_back(carta);
}

void Jugador::agregarFicha(Ficha ficha)
{
  fichas.push_back(ficha);
}

std::vector<Ficha> Jugador::obtenerFichas()
{
  return fichas;
}

std::vector<Carta> Jugador::getCartas(){
  return cartas;
  
}

int Jugador::obeterTotalFichas()
{
  return fichas.size();
}

Ficha Jugador::moverFicha()
{
  Ficha aux = fichas.back();
  fichas.pop_back();
  return aux;
}

void Jugador::sumarTerritorio()
{
  qTerritorios++;
}

int Jugador::getQterritorios()
{
  return qTerritorios;
}