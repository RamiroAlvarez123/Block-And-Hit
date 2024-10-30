#include <iostream>
#include "Usuario.h"


Usuario::Usuario(std::string nombre, int puntajeMax){
    this->nombre = nombre;
    this->puntajeMax = puntajeMax;
}

std::string Usuario::getNombre(){
    return nombre;
}
int Usuario::getPuntajeMax(){
    return puntajeMax;
}

void Usuario::setNombre(std::string nombre){
    this->nombre = nombre;
}
void Usuario::setPuntajeMax(int puntajeMax){
    this->puntajeMax = puntajeMax;
}
