#include "Territorio.h"
#include "Continente.h"
#include <iostream>
Territorio::Territorio(std::string nuevoNombre, int _id)
{
    nombre = nuevoNombre;
    id = _id;
}
// adicionar ficha
void Territorio::addFicha(Ficha ficha)
{
    fichas.push_back(ficha);
}
// eliminar ficha
void Territorio::deleteFicha()
{
    fichas.pop_back();
}


// set de reclamado
void Territorio::setReclamar(std::string jugador)
{
    reclamado = jugador;
}

std::string Territorio::getReclamado()
{
    return reclamado;
}

// contar las fichas
int Territorio::ContarFichas(std::string jugador)
{
    // Implementación para contar las fichas del jugador
    return 0;
}
// get de cantidad de fichas
int Territorio::GetQFichas()
{
    return fichas.size();
}

std::string Territorio::getNombre()
{
    return nombre;
}

int Territorio::getIdterritorio()
{
    return id;
}

void Territorio::agregarVecino(std::string tNombre)
{
    territoriosVecinos.push_back(tNombre);
}

std::vector<std::string> Territorio::getVecinos()
{
    return territoriosVecinos;
}

void Territorio::mostrarVecinos()
{
    for (int i = 0; i < territoriosVecinos.size(); i++)
    {
        std::cout<<i+1<<". "<<territoriosVecinos[i]<<std::endl;
    }
}
