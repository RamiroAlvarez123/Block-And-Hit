#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Juego.h"
#include "Reintentar.h"
#include "Menu.h"
#include "Pausa.h"
#include "Scoreboard.h"
#include "Win.h"
#include "NombreJugador.h"

class Scene {
private:
	b2World& _world;
	Juego* _juego;
	Reintentar* _reintentar;
    Menu* _menu;
    Pausa* _pausa;
    Scoreboard* _scoreboard;
    NombreJugador* _nombrejugador;
    Win* _win;
    bool _music = true;
public:
	Scene(b2World& world);

	void update();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool shouldExit() const;

	bool salir() const;
};
