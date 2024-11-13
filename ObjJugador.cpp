#include "ObjJugador.h"
#include <iostream>
#include <cstring>

ObjJugador::ObjJugador(){
    std::strncpy(_playerName, "N/A", 5);
	_playerName[5] = '\0';
	_puntos = 0;
}
ObjJugador::ObjJugador(const std::string& nombreJugador, int puntos){

    std::strncpy(_playerName, nombreJugador.c_str(), 5);
	_playerName[5] = '\0';
	_puntos = puntos;

}

std::string ObjJugador::getNombreJugador() const{ return _playerName; }
int ObjJugador::getPuntos() const{ return _puntos; }

