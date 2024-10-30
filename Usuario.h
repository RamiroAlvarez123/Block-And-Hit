#pragma once
#include <string>

class Usuario{

private:
    std::string nombre;
    int puntajeMax;
public:
    Usuario(std::string nombre = "", int puntaje = 0);
    std::string getNombre();
    int getPuntajeMax();
    void setNombre(std::string nombre);
    void setPuntajeMax(int puntaje);

};
