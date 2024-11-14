#include "Scene.h"
#include <iostream>

Scene::Scene(b2World& world) : _world(world)
{
	_juego = new Juego(world);
    _reintentar = new Reintentar();
    _menu = new Menu();
    _pausa = new Pausa();
    _scoreboard = new Scoreboard();
    _nombrejugador = new NombreJugador();
    _win = new Win();
}

void Scene::update() {
    if(_juego->getJuego()){
    _juego->update();
    if(_juego->getReintentar()){
        _juego->close();
        _reintentar->open();
    }if(_juego->getFinish()){
        _juego->close();
        _win->open();
    }

 }
}

void Scene::update(sf::Event event) {
if(_menu->getMenu()){

        _menu->update(event);

    if(_menu->getSelectedOpc() == 0){
        _menu->close(_music);

        if (_juego != nullptr) {
		delete _juego;
	}
	_juego = new Juego(_world);
    _nombrejugador->open();

    }else if(_menu->getSelectedOpc() == 1){
        _menu->close(_music);
        _scoreboard->open();

    }else if(_menu->getSelectedOpc() == 2){
        _menu->close(_music);

     }
}
else if(_nombrejugador->getInNombreJugador()){
            _nombrejugador->update(event);
            if(_nombrejugador->setNombreJugador()){
                _nombrejugador->close();
                _juego->setNombreJugador(_nombrejugador->getNombreJugador());
                _juego->open();
            }
    }
else if(_scoreboard->getScoreboard()){

        _scoreboard->update(event);
    if(_scoreboard->getSelectOpc() == 2){
        _scoreboard->close();
        _menu->open(_music);
    }
}

else if(_reintentar->getReintentar()){

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
else if(_pausa->getPausa()){
        _pausa->update(event);
        if(_pausa->getSelecOpc() == 0){
            _pausa->close();
            _juego->open();
        }else if(_pausa->getSelecOpc() == 1){
            _pausa->close();
            _menu->open();
        }
}

else if(_juego->getJuego()){
        _juego->update(event);
        if(_juego->getPausa()){
            _juego->close();
            _pausa->open();
        }
 }
else if(_win->getWin()){
        _win->update(event);
        if(_win->getSelected() == 0){
            _win->close();
            _menu->open();
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
    if(_nombrejugador->getInNombreJugador()){
        _nombrejugador->render(window);
    }
    if(_scoreboard->getScoreboard()){
        _scoreboard->render(window);
    }
    if(_reintentar->getReintentar()){
        _juego->render(window);
        _reintentar->render(window);
    }
    if(_pausa->getPausa()){
        _juego->render(window);
        _pausa->render(window);
    }

    if(_win->getWin()){
        _win->render(window);
    }

}

bool Scene::salir() const{
return _menu->getSalida();
}


