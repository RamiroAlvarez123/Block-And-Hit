#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Juego.h"
#include "Reintentar.h"

class Scene {
private:
	b2World& _world;
	Juego* _juego;
	Reintentar* _reintentar;

public:
	Scene(b2World& world);

	void update();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool shouldExit() const;
};
