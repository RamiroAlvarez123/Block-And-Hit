#pragma once
#include <iostream>
#include "ObjJugador.h"
#include <SFML/Graphics.hpp>

class ScoreboardFile{
private:

public:

    ScoreboardFile();

	int contarRegistros();
	void ordenarScoreboard();

	bool guardarJugador(const ObjJugador &jugador);

	ObjJugador leerJugador(int pos);

	void mostrarTop(sf::RenderWindow& window);
};























