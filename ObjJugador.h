#pragma once
#include <iostream>
class ObjJugador {

private:
char _playerName[6];
int _puntos;

public:
    ObjJugador();
    ObjJugador(const std::string& nombreJugador, int puntos);
    std::string getNombreJugador() const;
    int getPuntos() const;


};
