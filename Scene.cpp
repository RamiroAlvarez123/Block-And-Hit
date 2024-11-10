#include "Scene.h"
#include <iostream>

Scene::Scene(b2World& world) : _world(world)
{
	_juego = new Juego(world);

}

void Scene::update() {
    _juego->update();
}

void Scene::update(sf::Event event) {


}

void Scene::render(sf::RenderWindow& window)
{
    _juego->render(window);
}


