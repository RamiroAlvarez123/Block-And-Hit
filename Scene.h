#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Juego.h"

class Scene {
private:
	b2World& _world;
	Juego* _juego;

public:
	Scene(b2World& world);

	void update();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool shouldExit() const;
};
