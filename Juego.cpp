#include "Juego.h"
#include <iostream>


Juego::Juego(b2World& world) : _world(world)
{
    generateMap();
    generateStructures();
    spawnPlayer();
    _lifesTexture.loadFromFile("imgs/vidas.png");
	_lifesSprite.setTexture(_lifesTexture);
}

void Juego::update(){
    _world.Step(1.0f / 60, int32(10), int32(8));
    _player->cmd();
	_player->update();
}
void Juego::render(sf::RenderWindow& window){
    sf::View view = window.getView();
	sf::Vector2f playerPos = getCameraPosition();
	playerPos.x += 150; // La posicion del personaje + 150 para que se vea mas atras el personaje con respecto al centro.
	playerPos.y = (float(640) / 2); // El alto de la ventana dividido entre 2 para dejarlo fijo al medio.
	view.setCenter(playerPos);
	window.setView(view);

    _tiledMap->render(window);

    _player->render(window);
}


void Juego::generateMap(){
    _tiledMap = new TiledMap(_world);
}

void Juego::generateStructures(){
    _structures = new Structures(_world, _tiledMap->getMap());
}

void Juego::spawnPlayer() {
	_player = new Player(_world, _tiledMap->getPlayerSpawnPoint());
}

sf::Vector2f Juego::getCameraPosition()
{
	return _player->getPosition();
}

