#include "Scene.h"
#include <iostream>

Scene::Scene(b2World& world) : _world(world)
{
	_juego = new Juego(world);
    _reintentar = new Reintentar();
}

void Scene::update() {
    if(_juego->getJuego()){
    _juego->update();
    if(_juego->getReintentar()){
        _juego->close();
        _reintentar->open();
    }
}
}

void Scene::update(sf::Event event) {

if(_reintentar->getReintentar()){

    _reintentar->update(event);

    if(_reintentar->getSelectedOption() == 0){
        _reintentar->close();
        _juego->reintentar();
        _juego->open();
    }
}
}

void Scene::render(sf::RenderWindow& window)
{
    if(_juego->getJuego()){
       _juego->render(window);
    }
    if(_reintentar->getReintentar()){
        _juego->render(window);
        _reintentar->render(window);
    }
}


