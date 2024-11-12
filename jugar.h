#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Juego.h"

class Jugar
{
private:
	b2World& _world;
	Juego* _juego = nullptr;

	sf::Music _musicMenu;

	bool _jugar = false;
	bool _pause = false;
public:
	Jugar(b2World& world);

	void update();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool getJugar() const;

	bool getPause() const;

	void nuevoJuego();

	void reintentar();

	bool getReintentar();

	void crearJuego();

	void open();

	void close();
};
