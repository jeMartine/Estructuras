#include "Ficha.h"

// constructor
Ficha::Ficha(std::string nColor,  std::string nFigura) {
  color = nColor;
  figura = nFigura;
}
// get de  color 
std::string Ficha::obtenerColor()  {
    return color;
}
// getter de figura 
std::string Ficha::obtenerFigura()  {
    return figura;
}