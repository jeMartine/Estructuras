#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <cctype>
#include <limits>
#include <sstream>

#include "Risk.h"

using namespace std;

string ingresarComando();
void mensajeBienvenida();
int identificarComando(string cadena);
string separarEspacio(string cadena, bool parametro);
bool qParametros(string respuesta);
void crearArchivo(std::string nombreArchivo, std::string contenido);
void mostrarAyudaComando(const string &comando);
void infoInicializar(void);
void infoTurno(void);
void infoSalir(void);
void infoGuardar(void);
void infoGuardarComprimido(void);
void infoCostoConquista(void);
void infoConquistaMasBarata(void);

// entrega 2
void inicializarJuego(Risk *risk);
void fortificar(Risk *risk, bool inicializar);
void turno(Risk *risk);

void leerBinario(Risk *risk, string nombre_archivo);
void crearCartas(Risk *risk, const std::string &filename);
void poblarTerritorios(Risk *risk, const std::string &filename);
void poblarVecinos(Risk *risk, const std::string &filename);
void atacar(Risk *risk);
vector<string> leerArchivo(std::string &filename);
void poblarJuego(Risk *risk, vector<string> cadena);

std::map<char, int> contarFrecuencia(const std::string &cadena);
char MenorFrecuencia(std::map<char, int> &frecuencia);

int main()
{
  // instancia para la clase risk
  Risk risk;
  risk.crearContinente();
  crearCartas(&risk, "CartasJuego.txt");
  poblarTerritorios(&risk, "territorios.txt");
  poblarVecinos(&risk, "vecinosTerritorios.txt");
  // guarda la cadena ingresada por el usuario
  string respuesta;
  // mensaje de bienvenida
  mensajeBienvenida();
  // bandera para terminar el programa
  bool salir = false;
  // valor= variable usada en el switch case
  // qJugadores= cantidad de jugadores en la partida
  int valor, qJugadores;
  // turno= turno ingresado por el usuario
  // turnoPrueba= variable de turno para pruebas
  string turnoAux;
  // indica si hay algún ganador
  int ganador = -1;

  do
  {
    respuesta = ingresarComando();
    valor = identificarComando(respuesta);

    switch (valor)
    {
    // inicializar con archivo
    case 1:
    {
      risk.iniciarPartida();
      string nombreArchivo = separarEspacio(respuesta, true);

      poblarJuego(&risk, leerArchivo(nombreArchivo));
    }
    break;
    // inicializar
    case 2:

      if (!risk.estadoPartida())
      {
        inicializarJuego(&risk);
        fortificar(&risk, true);
        risk.turnosEnCero();
        cout << "\n-** El juego se ha inicializado correctamente. **-\n"
             << endl;
      }
      else
        cout << "Esta partida ya ha sido inicializada" << endl;

      break;
    case 3:
      turnoAux = separarEspacio(respuesta, true);

      if (!risk.estadoPartida())
      {
        cout << "-** Esta partida no ha sido inicializada correctamente **-\n";
      }
      else if (risk.estadoGanador())
      {
        cout << "-** Esta partida ya tuvo un ganador **-\n";
      }
      else if (risk.getNameJugadorEnTurno() == turnoAux)
      {
        turno(&risk);
      }
      else if (risk.jugadorExiste(turnoAux))
      {
        cout << "-** No es el turno del jugador <" << turnoAux << "> **-\n";
      }
      else
        cout << "-** El jugador <" << turnoAux << "> no forma parte de esta partida. **-\n";

      break;
      // salir
    case 4:
      salir = true;
      break;
      // guardar <nombre_archivo>
    case 5:
    {
      string nombreArchivo = separarEspacio(respuesta, true);
      // risk.guardarPartida();
      crearArchivo(nombreArchivo, risk.guardarPartida());
    }
    break;
      // guardar_comprimido <nombre_archivo>
    case 6:
    {
      string nombreArchivo = separarEspacio(respuesta, true);
      map<char, int> frecuencia = contarFrecuencia(nombreArchivo);

      std::cout << "Frecuencia de caracteres:" << std::endl;
      for (const auto &par : frecuencia)
      {
        std::cout << par.first << ": " << par.second << std::endl;
      }
      cout << "Caracteres por orden de menor frecuencia:" << endl;
      while (!frecuencia.empty())
      {
        char caracter = MenorFrecuencia(frecuencia);
        cout << "Caracter: " << caracter << ", Frecuencia: " << frecuencia[caracter] << endl;
      }
    }
    break;
      // costo_conquista <territorio>
    case 7:
      cout << "comando exitoso\n"
           << "costo_conquista <territorio>\n";
      break;
      // conquista_mas_barata
    case 8:
      cout << "comando exitoso\n"
           << "conquista_mas_barata\n";
      break;

    case 9:
      cout << "comando exitoso" << endl;
      break;

    case 10:
      cout << "help <comando>: Proporciona información de ayuda para los comandos de Risk.\n\nComandos disponibles:\n";
      cout << "inicializar - Inicializa un nuevo juego" << endl;
      cout << "turno - Muestra el turno" << endl;
      cout << "salir - Salir del programa" << endl;
      cout << "guardar -  Guarda el progreso" << endl;
      cout << "guardar_comprimido - Guarda el progreso en un formato .zip" << endl;
      cout << "costo_conquista - Muestra el costo de conquista de un territorio" << endl;
      cout << "conquista_mas_barata - Muestra costo de conquista mas barato" << endl;
      break;

    case 11:
      mostrarAyudaComando(respuesta.substr(respuesta.find(' ')));
      break;

    default:
      cout << "\"" << respuesta << "\""
           << " no se reconoce como un comando interno o parametros incorrectos.\n\n";
      break;
    }

  } while (salir == false);

  return 0;
}

// permite crear un archivo

void guardarBinario(Risk risk, string nombre_archivo)
{
  bool logro = true;
  ofstream archivo;

  do
  {
    archivo.open(nombre_archivo, ios::out);

    if (archivo.is_open())
    {
      archivo.write(reinterpret_cast<char *>(&risk), sizeof(Risk));
      archivo.close();
    }
    else
    {
      cout << "Error, el archivo no abrió";
      logro = false;
    }
  } while (!logro);
}

void leerBinario(Risk *risk, string nombre_archivo)
{

  bool logro = true;
  ifstream archivo;

  do
  {
    archivo.open(nombre_archivo, ios::in);

    if (archivo.is_open())
    {
      archivo.read(reinterpret_cast<char *>(risk), sizeof(Risk));
      archivo.close();
    }
    else
    {
      cout << "Error, el archivo no abrió";
      logro = false;
    }
  } while (!logro);
}

void crearArchivo(std::string nombreArchivo, std::string contenido)
{
  // Crear un objeto de ofstream y abrir el archivo en modo de escritura
  std::ofstream archivo(nombreArchivo);

  // Verificar si el archivo se abrió correctamente
  if (archivo.is_open())
  {
    // Escribir el contenido en el archivo
    archivo << contenido;

    // Cerrar el archivo después de escribir
    archivo.close();

    std::cout << "Partida guardada exitosamente." << std::endl;
  }
  else
  {
    std::cerr << "No se pudo guardar la partida." << std::endl;
  }
}

string separarEspacio(string cadena, bool parametro)
{
  string comando = cadena;
  size_t separar = cadena.find(' ');

  if (separar != string::npos)
  {
    if (parametro == false)
    {
      comando = cadena.substr(0, separar);
    }
    else
    {
      comando = cadena.substr(separar + 1);
    }
  }
  return comando;
}

void mostrarAyudaComando(const string &comando)
{
  string com = separarEspacio(comando, true);
  cout << endl;
  if (com == "inicializar")
  {
    cout << "inicializar <nombre_archivo>\n\n";
    infoInicializar();
  }
  else if (com == "turno")
  {
    cout << "turno <id_jugador>\n\n";
    infoTurno();
  }
  else if (com == "salir")
  {
    cout << "salir <>\n\n";
    infoSalir();
  }
  else if (com == "guardar")
  {
    cout << "guardar <nombre_archivo>\n\n";
    infoGuardar();
  }
  else if (com == "guardar_comprimido")
  {
    cout << "guardar_comprimido <nombre_archivo>\n\n";
    infoGuardarComprimido();
  }
  else if (com == "costo_conquista")
  {
    cout << "costo_conquista <territorio>\n\n";
    infoCostoConquista();
  }
  else if (com == "conquista_mas_barata")
  {
    cout << "conquista_mas_barata <>\n\n";
    infoConquistaMasBarata();
  }
  else if (com == "help")
  {
    cout << "help <comando>\n\n";
  }
  else
  {
    cout << "El comando \"" << com << "\" no tiene una descripción de ayuda.\n";
  }
}

void mensajeBienvenida()
{
  cout << "!Bienvenido a RISK?\nanimate a jugar :)\n";
}

string ingresarComando()
{
  string cadena;
  cout << "\n$";
  getline(cin, cadena);
  return cadena;
}

// permite identificar si solo se ingréso un comando con un solo parametro
bool qParametros(string respuesta)
{
  int espacios = 0;
  string p2 = separarEspacio(separarEspacio(respuesta, true), 0);

  for (int i = 0; i < respuesta.length(); i++)
  {
    if (respuesta[i] == ' ')
    {
      espacios++;
    }
  }

  if (espacios == 1 && p2 != "")
  {
    return true;
  }

  return false;
}

// recibe la primera parte del comando ingresado por el usuario y identificar a cual tipo corresponde
int identificarComando(string cadena)
{
  // guarda lo que ingresa el usuario
  string respuesta = separarEspacio(cadena, false);
  int valor = 0;

  if (respuesta == "inicializar" && qParametros(cadena) == true)
  {
    valor = 1;
  }
  else if (respuesta == "inicializar")
  {
    valor = 2;
  }
  else if (respuesta == "turno" && qParametros(cadena) == true)
  {
    valor = 3;
  }
  else if (respuesta == "salir")
  {
    valor = 4;
  }
  else if (respuesta == "guardar" && qParametros(cadena) == true)
  {
    valor = 5;
  }
  else if (respuesta == "guardar_comprimido" && qParametros(cadena) == true)
  {
    valor = 6;
  }
  else if (respuesta == "costo_conquista" && qParametros(cadena) == true)
  {
    valor = 7;
  }
  else if (respuesta == "conquista_mas_barata")
  {
    valor = 8;
  }
  else if (respuesta == "help" && qParametros(cadena) == true && separarEspacio(cadena, true) == "help")
  {
    valor = 9;
  }
  else if (respuesta.substr(0, respuesta.find(' ')) == "help" && qParametros(cadena) == false)
  {
    valor = 10;
  }
  else if (respuesta.substr(0, respuesta.find(' ')) == "help" && qParametros(cadena) == true)
  {
    valor = 11;
  }
  return valor;
}

void infoInicializar(void)
{
  cout << "Realiza las operaciones necesarias para inicializar el juego.\n\n El comando pregunta la cantidad de jugadores, para cada jugador su nombre o identificador, y luego, por turnos, pregunta a cada jugador en qué territorio desea ubicar sus unidades de ejército. \n\nEn cada turno, el jugador sólo puede indicar un único territorio a ocupar.\n"
       << endl;
}

void infoTurno(void)
{
  cout << "Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar).\n\n El comando informa al jugador cuántas unidades adicionales puede reclamar luego pregunta en cuáles de sus territorios las quiere asignar y en qué cantidad.\n\n A continuación pregunta la configuración del ataque, desde cuál territorio y hacia cuál territorio, verificando las condiciones ya descritas.\n\n Luego informa los valores obtenidos con los dados, y la cantidad de unidades que se ganan o pierden. \n\nEste proceso se repite hasta que alguno de los dos territorios se quede sin unidades, o hasta que el atacante decida detenerse. \n\nFinalmente, el comando pregunta al jugador los territorios vecinos que desea seleccionar para la fortificación, así como la cantidad de unidades que se trasladarán de uno al otro.\n"
       << endl;
}

void infoSalir(void)
{
  cout << "Termina la ejecución de la aplicación \n"
       << endl;
}

void infoGuardar(void)
{
  cout << "El estado actual del juego es guardado en un archivo de texto. \n\nEl archivo contiene la cantidad de jugadores, y para cada jugador almacena su nombre, su color de jugador, la cantidad de países que ocupa, el identificador de cada país junto con la cantidad de unidades de ejército en él, la cantidad de tarjetas que posee y el identificador de cada tarjeta.\n"
       << endl;
}

void infoGuardarComprimido(void)
{
  cout << "El estado actual del juego es guardado en un archivo binario (con extensión .bin) con la información (nombre del jugador, cantidad de países que ocupa, identificador de cada país, cantidad de unidades de ejército en paises, tarjetas que posee, identificador de cada tarjeta) comprimida.\n"
       << endl;
}

void infoCostoConquista(void)
{
  cout << "Calcula el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario. \n\nEl territorio desde donde debe atacar debe ser aquel que el jugador tenga controlado más cerca al dado por el jugador. \n\nEsta información se analiza desde el punto de vista del jugador que tiene el turno de juego.\n"
       << endl;
}

void infoConquistaMasBarata(void)
{
  cout << "En todos los territorios posibles, revisa cual puede implicar un menor número de unidades de ejército perdidas.\n\n Esta información se analiza desde el punto de vista del jugador que tiene el turno de juego." << endl;
}

void inicializarJuego(Risk *risk)
{
  int cantidadJugadores = 0;
  string nombreJug = "", continente = "", territorio = "", auxTerritorios = "";
  bool continenteValido = true, territorioValido = true;
  // cambio el estado de la partida a true
  risk->iniciarPartida();
  // pide la cantidad de jugadores
  // hasta que esté entre 3 y 6
  do
  {
    cout << "ingrese la cantidad de jugadores (3-6)" << endl;
    cantidadJugadores = stoi(ingresarComando());
  } while (cantidadJugadores < 3 || cantidadJugadores > 6);

  for (int i = 0; i < cantidadJugadores; i++)
  {
    cout << "Ingrese el nombre del jugador " << i + 1 << " : \n";
    nombreJug = ingresarComando();
    // creo un jugador en risk
    risk->CrearJugador(nombreJug, cantidadJugadores);
  }
  // verificar que se hace correctamente la incersión de datos

  cout << risk->infoJug() << endl;

  cout << "-** Reclamar territorio **-" << endl;
  do
  {
    cout << "\n  Turno de: " << risk->getNameJugadorEnTurno() << "\n  Color: " << risk->getColorJugadorEnTurno() << endl;
    // iniciarlizar tablero
    cout << "\tContinentes disponibles:" << endl;

    cout << risk->infoContinente() << endl;

    do
    {
      cout << "\tNombre del continente:" << endl;
      continente = ingresarComando();

      auxTerritorios = risk->infoTerritorios(continente);

      if (auxTerritorios != "")
      {
        cout << auxTerritorios;
        continenteValido = true;
      }
      else
      {
        cout << "\tNo se reconoce el continente ingresado" << endl;
        continenteValido = false;
      }

    } while (!continenteValido);

    do
    {
      cout << "\tNombre del Territorio:" << endl;
      territorio = ingresarComando();

      if (risk->estadoTerritorio(continente, territorio))
      {
        territorioValido = true;
      }
      else
      {
        cout << "\tNo se reconoce el territorio ingresado" << endl;
        territorioValido = false;
      }

    } while (!territorioValido);

    // mueve una ficha de un jugador al territorio del continente ingresado
    // cout << risk->infoJug() << endl;

    risk->moverFichasJugador(1, continente, territorio);
    risk->sumarPaisJugador();
    // cout << risk->infoJug() << endl;
    risk->turnoJugado();

  } while (risk->territoriosLibres());
}

void fortificar(Risk *risk, bool inicializar)
{
  string territorio = "", continente = "";
  int qFichas = 0;

  cout << "\n\t--**fortificar**--" << endl;

  do
  {
    cout << "\n  Turno de: " << risk->getNameJugadorEnTurno()
         << "\n  Color: " << risk->getColorJugadorEnTurno()
         << "\n  Fichas disponibles: " << risk->getFichasJugadorEnTurno()
         << "\nTerritorios disponibles: \n"
         << endl;

    cout << risk->territoriosJugador();

    do
    {
      cout << "Nombre territorio:\n";
      territorio = ingresarComando();
      continente = risk->buscarContinenteTerritorio(territorio);

      // cout << "continente: " << continente << endl;

      if (continente == "" || !risk->territorioJugador(continente, territorio))
      {
        cout << "\n-** Nombre de territorio no valido **-\n\n";
      }

    } while (continente == "" || !risk->territorioJugador(continente, territorio));

    do
    {
      cout << "Numero de fichas a mover: " << endl;
      qFichas = stoi(ingresarComando());
    } while (qFichas > risk->getFichasJugadorEnTurno());

    risk->moverFichasJugador(qFichas, continente, territorio);

    if (inicializar && risk->getFichasJugadorEnTurno() == 0)
      risk->turnoJugado();

  } while (risk->getFichasJugadorEnTurno() != 0);
}

void turno(Risk *risk)
{
  risk->nuevasTropasTerritorio();
  risk->nuevasTropasContiente();
  if (risk->getFichasJugadorEnTurno() > 0)
    fortificar(risk, false);
  else
    cout << " No se puede fortificar!\n  Fichas insuficientes!\n";
  atacar(risk);

  risk->turnoJugado();
}

void atacar(Risk *risk)
{
  string ataque = "";
  string contiAcaque = "";
  string defensa = "";
  int indContinete = 0;
  int indTerritorio = 0;
  int dadosAtacante[3] = {0};
  int dadosDefensor = 0;
  int totalDadosAtaque = 0;
  int dado1 = -1;
  int dado2 = -1;
  bool salir = false;

  // ataca
  cout << "\n\n--- FASE DE ATAQUE ---\n"
       << endl;
  cout << risk->territoriosJugador();

  do
  {
    cout << "Seleccione territorio:\n";
    ataque = ingresarComando();
    contiAcaque = risk->buscarContinenteTerritorio(ataque);

    if (contiAcaque == "" || !risk->territorioJugador(contiAcaque, ataque))
    {
      cout << "\n-** Nombre de territorio no valido **-\n\n";
    }

  } while (contiAcaque == "" || !risk->territorioJugador(contiAcaque, ataque));
  indContinete = risk->indiceContinente(contiAcaque);
  indTerritorio = risk->indiceTerritorio(indContinete, ataque);

  cout << "\nSelecciona para atacar\n";
  risk->mostrarVecinosTerritorio(indContinete, indTerritorio);

  do
  {
    defensa = ingresarComando();

    if (defensa == "" || !risk->validarDefensa(indContinete, indTerritorio, defensa))
    {
      cout << "\n-** Nombre de territorio no valido **-\n";
    }
  } while (defensa == "" || !risk->validarDefensa(indContinete, indTerritorio, defensa));

  // lanzar dados
  // jugada
  // ataca =3 dados, defiende = 2
  srand(time(NULL));
  do
  {
    dadosDefensor = 0;

    cout << "\n\n-- Defiende " << defensa << "- F: " << risk->fichasTerritorio(defensa) << " -- \n";
    // lanzamiento del defensor
    for (int i = 0; i < 2; i++)
    {

      int aux = 1 + rand() % (6);
      cout << "\t Dado " << i + 1 << ": " << aux << endl;
      dadosDefensor += aux;
    }
    cout << "-- Atacaca " << ataque << "- F: " << risk->fichasTerritorio(ataque) << "-- \n";

    // lanzamiento del atacante
    for (int i = 0; i < 3; i++)
    {
      int aux = 1 + rand() % (6);
      cout << "\t Dado " << i + 1 << ": " << aux << endl;
      dadosAtacante[i] = aux;
    }

    cout << "Seleccione dados para Comparar\n";

    do
    {
      cout << "Dado 1:\n";
      dado1 = stoi(ingresarComando());
    } while (dado1 <= 0 || dado1 > 3);

    do
    {
      cout << "Dado 2:\n";
      dado2 = stoi(ingresarComando());
    } while (dado2 <= 0 || dado2 > 3);

    dado1--;
    dado2--;
    totalDadosAtaque = dadosAtacante[dado1] + dadosAtacante[dado2];

    if (totalDadosAtaque > dadosDefensor)
    {
      cout << totalDadosAtaque << ">" << to_string(dadosDefensor) << "\nDefensa pierde una unidad\n";
      risk->deleteFichaTerritorio(defensa);
    }
    else if (totalDadosAtaque < dadosDefensor)
    {
      cout << totalDadosAtaque << "<" << to_string(dadosDefensor) << "\natacante pierde una unidad de ejercito\n";
      risk->deleteFichaTerritorio(ataque);
    }
    else if (totalDadosAtaque == dadosDefensor)
    {
      cout << totalDadosAtaque << " == " << to_string(dadosDefensor) << "\natacante pierde una unidad de ejercito\n";
      risk->deleteFichaTerritorio(ataque);
    }

    // cuando un territorio se queda sin fichas
    // el atacante pierde el territorio, quien defendió toma ese territorio
    if (risk->fichasTerritorio(ataque) == 0)
    {
      cout << "Que pena :c\n Acabas de perder " << ataque << " como tu territorio\n";
      risk->conquistarTerritorio(ataque, risk->buscarPropietario(defensa));
      salir = true;
    }

    // el defensor pierde el territorio, el que ataca (en turno) toma ese territorio
    if (risk->fichasTerritorio(defensa) == 0)
    {
      cout << "Genial! :D\n Acabas de ganar " << defensa << " como tu territorio\n";
      risk->conquistarTerritorio(defensa, risk->getNameJugadorEnTurno());
      salir = true;
      risk->sumarPaisJugador();

      // el jugador gana una carta
      Carta aux = risk->getCarta();
      cout << "\tHaz recibido carta\n\t " << aux.getTerritorio() << " : " << aux.getTropa() << endl;
      risk->agregarCarta(aux);
    }

    if (!salir)
    {
      cout << "Para terminar presione 0\n";
      if (ingresarComando() == "0")
        salir = true;
    }

  } while (salir == false);
}

void crearCartas(Risk *risk, const std::string &filename)
{

  ifstream input(filename.c_str());
  if (!input)
  {
    cout << "El archivo " << filename << " no se ha encontrado\n";
  }
  else
  {
    while (!input.eof())
    {
      string territorio, tropa;
      input >> territorio >> tropa;
      for (int i = 0; i < territorio.length(); i++)
      {
        if (territorio[i] == '_')
          territorio[i] = ' ';
      }

      risk->agregarCartas(territorio, tropa);
    }
    input.close();
  }
}

void poblarTerritorios(Risk *risk, const std::string &filename)
{
  int continente = 0;
  ifstream input(filename.c_str());
  if (!input)
  {
    cout << "El archivo " << filename << " no se ha encontrado\n";
  }
  else
  {
    string linea;
    while (getline(input, linea))
    {
      stringstream ss(linea);
      int id;
      string nombre;
      char delimiter; // Para leer las comas

      // Leer el ID del país y omitir la coma
      if (!(ss >> id >> delimiter))
      {
        cerr << "Error al leer el ID de un país." << endl;
        continue; // Ir a la siguiente línea si hay un error
      }
      // Omitir los espacios en blanco después de la coma
      ss >> ws;

      // Leer el nombre del país hasta el final de la línea
      if (!getline(ss, nombre))
      {
        cerr << "Error al leer el nombre de un país." << endl;
        continue;
      }
      if (nombre != "cambio")
        risk->agregarTerritorio(continente, nombre, id);
      if (nombre == "cambio")
        continente++;
  }
  input.close();
}
}

void poblarVecinos(Risk *risk, const std::string &filename)
{
  int continente = 0;
  int terri = 0;
  vector<string> vecinos;
  ifstream input(filename.c_str());
  if (!input)
  {
    cout << "El archivo " << filename << " no se ha encontrado\n";
  }
  else
  {
    while (!input.eof())
    {
      string lectura;
      input >> lectura;

      for (int i = 0; i < lectura.length(); i++)
      {
        if (lectura[i] == '_')
          lectura[i] = ' ';
      }

      if (lectura != "vc")
      {
        if (lectura != "cc")
        {
          risk->agregarVecinoTerritorio(continente, terri, lectura);
        }
      }

      if (lectura == "vc")
      {
        terri++;
      }
      if (lectura == "cc")
      {
        continente++;
        terri = 0;
      }
    }
    input.close();
  }
}

vector<string> leerArchivo(std::string &filename)
{

  ifstream archivo(filename); // Abrir el archivo en modo de lectura

  vector<string> contenido; // contenido del archivo

  if (archivo.is_open())
  {
    string linea;
    while (!archivo.eof())
    {
      archivo >> linea;
      contenido.push_back(linea);
    }
    archivo.close(); // Cerrar el archivo después de la lectura
  }
  else
  {
    cerr << "No se pudo abrir el archivo." << endl;
  }

  return contenido;
}

// pobla las estructutas del juego
void poblarJuego(Risk *risk, vector<string> cadena)
{
  int continente = 0;
  int indJugador = 0;
  int indCartas = 0;
  int indTerritorio = 0;
  int indCarta = 0;
  bool jugador = true; // empezamos poblando los jugadores
  bool terri = false;
  bool carta = false;
  int qJugadores = 0;
  int linea = 0;

  // cout<<cadena<<endl;

  qJugadores = stoi(cadena[0]);

  for (int i = 1; i < cadena.size(); i++)
  {
    if (jugador)
    {
      if (cadena[i] != "TTR")
      {
        risk->CrearJugador(cadena[i], qJugadores);
      }
      else
      {
        jugador = false; // termino de poblar jugadores
        terri = true;    // empiezo a poblar territorios
        i++;
      }
    }

    if (terri)
    {
      if (cadena[i] != "CAR")
      {
        if (cadena[i] != "TTR")
        {
          // cout << cadena[i] << " : " << cadena[i + 1] << "->" << indJugador << endl;
          risk->poblarTerritorio(cadena[i], stoi(cadena[i + 1]), risk->getNombreJugador(indJugador), risk->getColorJugador(indJugador));
          i++;
        }
        else
        {
          indJugador++;
        }
      }
      else
      {
        jugador = false;
        terri = false;
        carta = true;
        indJugador = 0;
        i++;
      }
    }

    if (carta)
    {
      if (cadena[i] != "CAR")
      {
        // cout << cadena[i] << " : " << cadena[i + 1] << " ->" << indCartas<<endl;
        risk->agregarCartaJugador(cadena[i], cadena[i + 1], indCarta);
        i++;
      }
      else
      {
        indCartas++;
      }
    }
  }
}

std::map<char, int> contarFrecuencia(const std::string &cadena)
{
  std::map<char, int> frecuencia;

  for (char caracter : cadena)
  {
    frecuencia[caracter]++;
  }

  return frecuencia;
}

char MenorFrecuencia(std::map<char, int> &frecuencia)
{
  char caracterMenorFrecuencia = '\0';
  int menorFrecuencia = std::numeric_limits<int>::max();

  // Encontrar caracter con la menor frecuencia
  for (const auto &par : frecuencia)
  {
    if (par.second < menorFrecuencia)
    {
      menorFrecuencia = par.second;
      caracterMenorFrecuencia = par.first;
    }
  }

  // Eliminar el caracter con la menor frecuencia del mapa
  frecuencia.erase(caracterMenorFrecuencia);

  return caracterMenorFrecuencia;
}
