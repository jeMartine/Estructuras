#include "Risk.h"
#include "Territorio.h"
#include <iostream>
#include <random>
Risk::Risk()
{
  Partida = false;
  Ganador = false;
  turnoActual = 0;
  Totalturnos = 0;
}

int Risk::LanzarDado()
{
  numeroAleatorio(1,6);

}
// pone la bandera de partida en verdadero
void Risk::iniciarPartida()
{
  Partida = true;
}

bool Risk::estadoPartida()
{
  return Partida;
}

void Risk::asignarGanador()
{
  // Implementación para asignar un ganador y terminar la partida
}

bool Risk::estadoGanador()
{
  return Ganador;
}

// pone el contador de turnos en cero para volver a empezar desde el jugador 0
void Risk::turnosEnCero()
{
  Totalturnos = 0;
  turnoActual = 0;
}

void Risk::agregarTerritorio(int continente, std::string nombreTerritorio, int id)
{
  continentes[continente].AddTerritorio(nombreTerritorio, id);
}

void Risk::agregarVecinoTerritorio(int continente, int territorio, std::string nombreVecino)
{
  continentes[continente].agregarVecino(territorio, nombreVecino);
}

void Risk::mostrarVecinosTerritorio(int conti, int terri)
{
  std::vector<std::string> vecinos = continentes[conti].mostrarVecinos(terri);
  // recorro los vecinos
  for (int i = 0; i < vecinos.size(); i++)
  {
    if (!territorioJugador(buscarContinenteTerritorio(vecinos[i]), vecinos[i]))
      std::cout << i + 1 << buscarFichasTerritorio(vecinos[i]) << std::endl;
  }
}

// retorna una cadena de caracteres con el nombre del territorio y la cantidad de fichas que pose este territorio
std::string Risk::buscarFichasTerritorio(std::string terri)
{
  std::string retorno = "";
  for (int i = 0; i < continentes.size(); i++)
  {
    for (int j = 0; j < continentes[i].cantidadTerritorios(); j++)
    {
      if (continentes[i].getNombreTerritorio(j) == terri)
      {
        retorno += +". " + continentes[i].getNombreTerritorio(j) + " \t- F: " + std::to_string(continentes[i].getFichasEnTerritorio(j)) + "\tP:" + continentes[i].reclamado(j);
        return retorno;
      }
    }
  }
}

//retorna la cantidad de fichas de un territorio
int Risk::fichasTerritorio(std::string terri){
  int retorno = 0;
  for (int i = 0; i < continentes.size(); i++)
  {
    for (int j = 0; j < continentes[i].cantidadTerritorios(); j++)
    {
      if (continentes[i].getNombreTerritorio(j) == terri)
      {
        return continentes[i].getFichasEnTerritorio(j);
      }
    }
  }
}

//elimina una ficha de un territorio
bool Risk::deleteFichaTerritorio(std::string terri){
  for (int i = 0; i < continentes.size(); i++)
  {
    for (int j = 0; j < continentes[i].cantidadTerritorios(); j++)
    {
      if (continentes[i].getNombreTerritorio(j) == terri)
      {
        continentes[i].eliminarFichaTerritorio(j);
        return true;
      }
    }
  }
  return false;
}

bool Risk::validarDefensa(int indContiente, int indterritorio, std::string territorio)
{
  std::vector<std::string> vecinos = continentes[indContiente].mostrarVecinos(indterritorio);
  for(int i=0; i<vecinos.size();i++){
    if(territorio==vecinos[i])
      return true;
  }
  return false;
}


void Risk::crearContinente()
{

  // vamos a crear los contienentes
  Continente continente1("america del norte");
  Continente continente2("america del sur");
  Continente continente3("europa");
  Continente continente4("africa");
  Continente continente5("asia");
  Continente continente6("australia");

  // Agregar los continentes al tablero del juego
  continentes.push_back(continente1);
  continentes.push_back(continente2);
  continentes.push_back(continente3);
  continentes.push_back(continente4);
  continentes.push_back(continente5);
  continentes.push_back(continente6);
}

void Risk::agregarCartas(std::string territorio, std::string tropa)
{
  cartas.push_back(Carta(territorio, tropa));
}

// aumenta la cantiad de turnos realizados, para poder avanzar al siguiente turno
// esta funcion reliza el avanzar en los jugadores mostradondo el nombre del jugador

void Risk::turnoJugado()
{
  Totalturnos += 1;
  turnoActual = Totalturnos % jugadores.size();
}

// retorna el nombre de los continentes disponible
std::string Risk::infoContinente()
{
  std::string retorno = "";
  int contador = 0;
  for (int i = 0; i < 6; i++)
  {
    if (continentes[i].getTerritoriosOcupados() != continentes[i].cantidadTerritorios())
    {
      retorno += "\t" + std::to_string(contador + 1) + ". " + continentes[i].obtenerNombre() + "\n";
      contador++;
    }
  }
  return retorno;
}

// guarda en una variable los territorios de un continente
// si el nombre del continente no existe, retorna ""
std::string Risk::infoTerritorios(std::string nameContinente)
{
  std::string retorno = "";
  int qTerritorios = 0, cont = 0;

  for (int i = 0; i < 6; i++)
  {
    if (continentes[i].obtenerNombre() == nameContinente)
    {

      qTerritorios = continentes[i].cantidadTerritorios();

      for (int terri = 0; terri < qTerritorios; terri++)
      {
        if (continentes[i].reclamado(terri) == "")
        {
          retorno += "\t" + std::to_string(cont + 1) + ". " + continentes[i].getNombreTerritorio(terri) + "\n";
          cont++;
        }
      }
      i = 6;
    }
    else
      retorno = "";
  }
  return retorno;
}
// retorna una cadena de caracteres con salida en pantalla donde se indican los continentes
// disponibles para consultar los territorios disponibles para conquistar.

bool Risk::estadoTerritorio(std::string nameContinente, std::string nameTerritorio)
{
  for (int i = 0; i < 6; i++)
  {
    if (continentes[i].obtenerNombre() == nameContinente)
    {
      return continentes[i].territorioValido(nameTerritorio);
    }
  }
  return false;
}

// recibo el nombre de un jugador y lo guardo en el vector de jugadores
void Risk::CrearJugador(std::string nombre, int qJugadores)
{

  int total = qUnidades(qJugadores);
  Jugador aux(nombre, colorJugador());
  Ficha batallon(colorJugador(), "infanteria");
  // agrega qUnidades de infanteria al jugador
  while (total != 0)
  {
    aux.agregarFicha(batallon);
    total--;
  }
  // guardo el jugador
  jugadores.push_back(aux);
}

// retorna el color que se le debe asignar a un jugador
std::string Risk::colorJugador()
{
  switch (jugadores.size() + 1)
  {
  case 1:
    return "verde";
  case 2:
    return "azul";
  case 3:
    return "rojo";
  case 4:
    return "amarillo";
  case 5:
    return "negro";
  case 6:
    return "gris";
  }
  return NULL;
}

// identifica las unidad ed de batallón inicial
int Risk::qUnidades(int qJugadores)
{
  switch (qJugadores)
  {
  case 3:
    return 35;
  case 4:
    return 30;
  case 5:
    return 25;
  case 6:
    return 20;
  }
  return -1;
}

// función de depuración
std::string Risk::infoJug()
{
  std::string retorno = "";

  retorno = jugadores[0].obtenerNombreJugador() + " : " + std::to_string(jugadores[0].obeterTotalFichas());
  return retorno;
}

// retorna el nombre del jugador en turno
std::string Risk::getNameJugadorEnTurno()
{
  return jugadores[turnoActual].obtenerNombreJugador();
}

// retorna el color del juagdor en turno
std::string Risk::getColorJugadorEnTurno()
{
  return jugadores[turnoActual].obtenerColor();
}
// retorna la cantidad de fichas que tiene el jugador en turno
int Risk::getFichasJugadorEnTurno()
{
  return jugadores[turnoActual].obeterTotalFichas();
}

// mueve una cantidad de fichas de un jugador a un territorio de un continente en especifico
// y permite ocupar ese territorio por el jugador
bool Risk::moverFichasJugador(int qFichas, std::string continente, std::string territorio)
{
  int iContinente = indiceContinente(continente);
  int iTerritorio = indiceTerritorio(iContinente, territorio);

  if (jugadores[turnoActual].obeterTotalFichas() >= qFichas)
  {
    for (int i = 0; i < qFichas; i++)
    {
      continentes[iContinente].ocuparTerritorio(jugadores[turnoActual].moverFicha(), iTerritorio, jugadores[turnoActual].obtenerNombreJugador());
    }

    return true;
  }
  else
    return false;
}


bool Risk::conquistarTerritorio(std::string terri, std::string nombreJugador)
{
  Ficha batallon(colorJugador(), "infanteria");

  for (int i = 0; i < continentes.size(); i++)
  {
    for (int j = 0; j < continentes[i].cantidadTerritorios(); j++)
    {
      if (continentes[i].getNombreTerritorio(j) == terri)
      {
        continentes[i].ocuparTerritorio(batallon, j, nombreJugador);

        return true;
      }
    }
  }
  return false;
}

std::string Risk::getColorJugador(int indice){
  return jugadores[indice].obtenerColor();
}

std::string Risk::getNombreJugador(int indice){
  return jugadores[indice].obtenerNombreJugador();
}

bool Risk::poblarTerritorio(std::string terri, int qFichas, std::string nombreJugador, std::string colorJug)
{
  Ficha batallon(colorJug, "infanteria");
  
  for (int i = 0; i < continentes.size(); i++)
  {
    for (int j = 0; j < continentes[i].cantidadTerritorios(); j++)
    {
      if (continentes[i].getNombreTerritorio(j) == terri)
      {
        //std::cout<<"se encontró el territorio "<<terri<<std::endl;
        continentes[i].ocuparTerritorio(batallon, j, nombreJugador);
        moverFichasJugador(qFichas, continentes[i].obtenerNombre(), terri);

        return true;
      }
    }
  }
  return false;
}

std::string Risk::buscarPropietario(std::string terri){
  for (int i = 0; i < continentes.size(); i++)
  {
    for (int j = 0; j < continentes[i].cantidadTerritorios(); j++)
    {
      if (continentes[i].getNombreTerritorio(j) == terri)
      {
        return continentes[i].reclamado(j);
      }
    }
  }
}

void Risk::sumarPaisJugador()
{
  // sumo 1 al total de territorios del jugador
  jugadores[turnoActual].sumarTerritorio();
}

// busca en el vector de continentes el indice de un continente
int Risk::indiceContinente(std::string continente)
{
  for (int i = 0; i < continentes.size(); i++)
  {
    if (continentes[i].obtenerNombre() == continente)
      return i;
  }
  return -1;
}

// busca en el vector de territorio todos los indices
int Risk::indiceTerritorio(int iContinente, std::string territorio)
{
  for (int i = 0; i < continentes[iContinente].cantidadTerritorios(); i++)
  {
    if (continentes[iContinente].getNombreTerritorio(i) == territorio)
    {
      return i;
    }
  }
  return -1;
}

// indica si todos los territorios de todos los continentes han sido ocupados
bool Risk::territoriosLibres()
{
  int qContiOcupados = 0;
  for (int i = 0; i < continentes.size(); i++)
  {
    if (continentes[i].getTerritoriosOcupados() == continentes[i].cantidadTerritorios())
      qContiOcupados++;
  }

  if (qContiOcupados == continentes.size())
    return false;
  return true;
}

// retorna una cadena de caracteres con la salida a la pantalla de los territorios que le pertenecen al usuairo en turno
// usada para mostrar en fortificar y decirle al usuario cuales son los territorios con la cantidad de fichas que tiene en cada uno

std::string Risk::territoriosJugador()
{
  std::string retorno = "";
  int contador = 0;

  for (int i = 0; i < continentes.size(); i++)
  {
    for (int terri = 0; terri < continentes[i].cantidadTerritorios(); terri++)
    {
      if (continentes[i].reclamado(terri) == jugadores[turnoActual].obtenerNombreJugador())
      {
        retorno += std::to_string(contador + 1) + ". " + continentes[i].getNombreTerritorio(terri) + " - F: " + std::to_string(continentes[i].getFichasEnTerritorio(terri)) + "\n";
        contador++;
      }
    }
  }
  return retorno;
}

// función que crea la cadena de caracteres que va a ser guardada con relación a la información de un jugador
std::string Risk::territoriosJugadorArch(int iJugador)
{
  std::string retorno = "";
  int contador = 0;

  for (int i = 0; i < continentes.size(); i++)
  {
    for (int terri = 0; terri < continentes[i].cantidadTerritorios(); terri++)
    {
      if (continentes[i].reclamado(terri) == jugadores[iJugador].obtenerNombreJugador())
      {
        retorno += espacioPorRaya(continentes[i].getNombreTerritorio(terri))+ " " + std::to_string(continentes[i].getFichasEnTerritorio(terri)) +"\n";
        contador++;
      }
    }
  }
  return retorno;
}

std::string Risk::espacioPorRaya(std::string cadena){
  for(int i=0; i<cadena.length(); i++){
    if(cadena[i]==' ')
      cadena[i]='_';
  }
  return cadena;
}

// busca y regresa el nombre del contiente del territorio que ingresó el usuario
// usada en reforzar para poder validar el continente al cual pertecene el territorio y usar
// la función declarada en Risk::moverFichasJugadory validar despúes que el territorio de ese continente
// le pertenece al jugador en turno.

std::string Risk::buscarContinenteTerritorio(std::string territorio)
{
  for (int conti = 0; conti < continentes.size(); conti++)
  {

    for (int terri = 0; terri < continentes[conti].cantidadTerritorios(); terri++)
    {

      if (continentes[conti].getNombreTerritorio(terri) == territorio)
        return continentes[conti].obtenerNombre();
    }
  }
  return "";
}

// revisa que el territorio ingresado corresponda al jugador que se encuentra en turno
// usada en reforzar para que solo pueda ingresar el nombre de un territorio que le pertenece al jugador que está reforzando
bool Risk::territorioJugador(std::string continente, std::string territorio)
{
  int conti = indiceContinente(continente);
  int iTerritorio = indiceTerritorio(conti, territorio);

  if (continentes[conti].reclamado(iTerritorio) == jugadores[turnoActual].obtenerNombreJugador())
    return true;
  return false;
}

// compara con los jugadores de la partida el nombre ingresado
// retorna true, cuando el nombre ingresado es el mismo del jugador actual
bool Risk::esTurnoJugador(std::string nombreIngresado)
{
  for (int i = 0; i < jugadores.size(); i++)
  {
    if (jugadores[i].obtenerNombreJugador() == nombreIngresado)
    {
      if (jugadores[turnoActual].obtenerNombreJugador() == nombreIngresado)
        return true;
    }
  }
  return false;
}

// busca los nombres de los jugadores y retorna true cuando el nombre del jugador existe
// en la partida actual
bool Risk::jugadorExiste(std::string nombreIngresado)
{
  for (int i = 0; i < jugadores.size(); i++)
  {
    if (jugadores[i].obtenerNombreJugador() == nombreIngresado)
      return true;
  }
  return false;
}

std::string Risk::cartasDeJugador(int indJugador)
{
  std::string retorno="";
  std::vector<Carta> cartasAux = jugadores[indJugador].getCartas();

  if(!cartasAux.empty()){
    for(int i =0; i<cartasAux.size(); i++){
      retorno+=espacioPorRaya(cartasAux[i].getTerritorio())+" "+cartasAux[i].getTropa()+"\n";
    }
  }
  return retorno;
}


std::string Risk::guardarPartida()
{

  //crear primer bloque de jugadores
  std::string mensaje = std::to_string(jugadores.size()) + "\n";
  for (int i = 0; i < jugadores.size(); i++)
  {
    mensaje+=jugadores[i].obtenerNombreJugador()+"\n";
  }
  //indica el inicio de los territorios de jugadores
  mensaje+="TTR\n";
  for (int i = 0; i < jugadores.size(); i++)
  {
    mensaje += territoriosJugadorArch(i);
    //cambio de territorios al otro jugador
    mensaje+="TTR\n";           
  }
  //inicio de las cartes de cada jugador
  mensaje +="CAR\n";

  for (int i = 0; i < jugadores.size(); i++)
  {
    mensaje += cartasDeJugador(i);
    //cambio de territorios al otro jugador
    mensaje+="CAR\n";           
  }

  std::cout<<mensaje<<std::endl;
  return mensaje;
}

void Risk::nuevasTropasTerritorio()
{
  int qTerriJuga = jugadores[turnoActual].getQterritorios();
  int agregar = round(qTerriJuga / 3.0);

  if (agregar > 0)
    std::cout << "Ha recibido " << agregar << " tropas por los territorios que posee\n";
  // agrego la cantidad de fichas que le corresponden
  for (int i = 0; i < agregar; agregar--)
  {
    Ficha aux(getColorJugadorEnTurno(), "infanteria");
    jugadores[turnoActual].agregarFicha(aux);
  }
}

// buscar en cada continente si todos los paises que tiene, estan gobernados por el jugador en turno
void Risk::nuevasTropasContiente()
{
  int qNuevasTropas = 0;
  for (int i = 0; i < continentes.size(); i++)
  {
    if (continentes[i].continenteOcupado(getNameJugadorEnTurno()))
      if (continentes[i].obtenerNombre() == "america del sur" ||
          continentes[i].obtenerNombre() == "australia")
        qNuevasTropas += 2;
      else if (continentes[i].obtenerNombre() == "america del norte" ||
               continentes[i].obtenerNombre() == "europa")
        qNuevasTropas += 5;
      else if (continentes[i].obtenerNombre() == "africa")
        qNuevasTropas += 3;
      else if (continentes[i].obtenerNombre() == "aisa")
        qNuevasTropas += 7;
  }

  if (qNuevasTropas > 0)
    std::cout << "Ha recibido " << qNuevasTropas << " tropas por los contientes que posee\n";

  for (int i = 0; i < qNuevasTropas; qNuevasTropas--)
  {
    Ficha aux(getColorJugadorEnTurno(), "infanteria");
    jugadores[turnoActual].agregarFicha(aux);
  }
}

//agrega una carta al conquistar un terreno al jugador en turno
void Risk::agregarCarta(Carta cartaAux){
  jugadores[turnoActual].agregarCarta(cartaAux);
}

// retorna una carta aleatoriamente del fajo de cartas del juego
Carta Risk::getCarta()
{
  int nCarta = numeroAleatorio(0, cartas.size() - 2);
  std::vector<Carta>::iterator it = cartas.begin();
  // std::cout<<nCarta<<std::endl;
  Carta cartaAux = cartas[nCarta];

  while (nCarta > 0)
  {
    it++;
    nCarta--;
  }

  cartas.erase(it);

  return cartaAux;
}

int Risk::numeroAleatorio(int minimo, int maximo)
{
  // Inicializar la semilla para generar números aleatorios
  srand(time(NULL));
  // Generar un número aleatorio en el rango [minimo, maximo]
  int numeroAleatorio = minimo + rand() % (maximo - minimo + 1);
  return numeroAleatorio;
}

void Risk::agregarCartaJugador(std::string terri, std::string tropa, int indJugador){
  Carta aux(terri, tropa);
  jugadores[indJugador].agregarCarta(aux);
}
