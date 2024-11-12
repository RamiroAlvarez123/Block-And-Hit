#include "Scene.h"
#include <iostream>

Scene::Scene(b2World& world) : _world(world)
{
	_juego = new Juego(world);
    _reintentar = new Reintentar();
    _menu = new Menu();
    _pausa = new Pausa();
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
    if(_menu->getMenu()){
        _menu->update(event);
    if(_menu->getSelectedOpc() == 0){
        _menu->close();
        if (_juego != nullptr) {
		delete _juego;
	}
	_juego = new Juego(_world);
        _juego->open();
    }else if(_menu->getSelectedOpc() == 1){

    }else if(_menu->getSelectedOpc() == 2){

     }
    }

if(_reintentar->getReintentar()){

    _reintentar->update(event);

    if(_reintentar->getSelectedOption() == 0){
        _reintentar->close();
        _juego->reintentar();
        _juego->open();
    }else if(_reintentar->getSelectedOption() == 1){
        _reintentar->close();
        _juego->close();
        _menu->open();
    }
}
    if(_pausa->getPausa()){
        _pausa->update(event);
        std::cout<<_pausa->getSelecOpc();
        if(_pausa->getSelecOpc() == 0){
            _pausa->close();
            _juego->open();
        }else if(_pausa->getSelecOpc() == 1){
            _pausa->close();
            _menu->open();
        }
    }

    if(_juego->getJuego()){
        _juego->update(event);
        if(_juego->getPausa()){
            _juego->close();
            _pausa->open();
        }
    }

}

void Scene::render(sf::RenderWindow& window)
{
    if(_menu->getMenu()){
        _menu->render(window);
    }
    if(_juego->getJuego()){
       _juego->render(window);
    }
    if(_reintentar->getReintentar()){
        _juego->render(window);
        _reintentar->render(window);
    }
    if(_pausa->getPausa()){
        _juego->render(window);
        _pausa->render(window);
    }
}


