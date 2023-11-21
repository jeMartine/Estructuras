#ifndef FICHA_H
#define FICHA_H

#include <string>

class Ficha {
public:
    Ficha(std::string nColor,  std::string nFigura);
    
    // Getters
    std::string obtenerColor() ;
    std::string obtenerFigura() ;

private:
    std::string color;
    std::string figura;
};

#endif // FICHA_H