#include "Continente.h"
#include "Territorio.h"
// constructor
Continente::Continente(std::string nNombre)
{
  nombre = nNombre;
  territoriosOcupados = 0;
}

std::string Continente::obtenerNombre()
{
  return nombre;
}

/*
//get color
std::string Continente::obtenerColor() {
    return color;
}
//set color
void Continente::establecerColor( std::string nuevoColor) {
    color = nuevoColor;

}
*/
// la parte ocupar el territorio
void Continente::ocuparTerritorio(Ficha ficha, int nTerritorio, std::string nombreJugador)
{
  territorios[nTerritorio].addFicha(ficha);
  territorios[nTerritorio].setReclamar(nombreJugador);
  territoriosOcupados++;
}

int Continente::cantidadTerritorios()
{
  return territorios.size();
}

int Continente::getTerritoriosOcupados()
{
  return territoriosOcupados;
}

std::string Continente::getNombreTerritorio(int indice)
{
  return territorios[indice].getNombre();
}

int Continente::getIdTerritorio(int indice)
{
  return territorios[indice].getIdterritorio();
}

// buscar el nombre de un territorio en un continente y si existe, retorna true
bool Continente::territorioValido(std::string territorio)
{
  for (int i = 0; i < territorios.size(); i++)
  {
    if (territorios[i].getNombre() == territorio && territorios[i].getReclamado() == "")
      return true;
  }
  return false;
}

// indica si un continente está completamente ocupado por un jugador
bool Continente::continenteOcupado(std::string nombreJugador)
{
  int posee = 0;
  for (int i = 0; i < territorios.size(); i++)
  {
    if (territorios[i].getReclamado() != nombreJugador)
      return false;
  }
  return true;
}

// adicionar al continente el territorio escogido por el usuario //// por eso se pasa por referencia
void Continente::AddTerritorio(std::string nombre, int _id)
{
  Territorio territorio(nombre, _id);
  territorios.push_back(territorio);
}

std::string Continente::reclamado(int indice)
{
  return territorios[indice].getReclamado();
}

int Continente::getFichasEnTerritorio(int indice)
{
  return territorios[indice].GetQFichas();
}

// agrega el nombre de un pais vecino a un territorio
void Continente::agregarVecino(int territorio, std::string nombreVecino)
{
  territorios[territorio].agregarVecino(nombreVecino);
}

std::vector<std::string> Continente::mostrarVecinos(int territorio)
{
  return territorios[territorio].getVecinos();
}

//elimina una ficha de un territorio
void Continente::eliminarFichaTerritorio(int terri){
  territorios[terri].deleteFicha();
}
