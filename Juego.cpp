#include "Juego.h"
#include <iostream>


Juego::Juego(b2World& world) : _world(world)
{
    generateMap();
    generateStructures();
    spawnPlayer();
    _lifesTexture.loadFromFile("imgs/vidas.png");
	_lifesSprite.setTexture(_lifesTexture);

	_font.loadFromFile("font/PixelOperator8.ttf");
	_pointsText.setFont(_font);
	_pointsText.setCharacterSize(24);
	_pointsText.setFillColor(sf::Color::White);
	_pointsText.setOutlineThickness(2);
	_pointsText.setOutlineColor(sf::Color::Black);
}

void Juego::update(){
    // Update Lifes
	int lifesWidth = 241;
	int lifesHeight = 55;

	switch (_lifes) {
	case 4:
		_lifesSprite.setTextureRect({ 16, lifesHeight * 0, lifesWidth, lifesHeight });
		break;
	case 3:

		_lifesSprite.setTextureRect({ 16, lifesHeight * 1.17, lifesWidth, lifesHeight });
		break;
	case 2:

		_lifesSprite.setTextureRect({ 16, lifesHeight * 2.34, lifesWidth, lifesHeight });
		break;
	case 1:

		_lifesSprite.setTextureRect({ 16, lifesHeight * 3.50, lifesWidth, lifesHeight });
		break;
    case 0:

		_lifesSprite.setTextureRect({ 16, lifesHeight * 4.64, lifesWidth, lifesHeight });
		break;
	default:
		break;
	}

    _world.Step(1.0f / 60, int32(10), int32(8));

    _player->cmd();
	_player->update();

    if(_player->isDead()){
        _buffer.loadFromFile("sounds/explosion.wav");
        _sound.setBuffer(_buffer);
        _sound.play();
        respawn();
        _lifes--;

    }
}
void Juego::render(sf::RenderWindow& window){
    sf::View view = window.getView();
	sf::Vector2f playerPos = getCameraPosition();
	playerPos.x += 150; // La posicion del personaje + 150 para que se vea mas atras el personaje con respecto al centro.
	playerPos.y = (float(640) / 2.7); // El alto de la ventana dividido entre 2 para dejarlo fijo al medio.
	view.setCenter(playerPos);
	window.setView(view);

    _tiledMap->render(window);

    _player->render(window);

    sf::Vector2f viewCorner = window.mapPixelToCoords(sf::Vector2i(0, 0), view);
	_lifesSprite.setPosition(viewCorner.x + 15, viewCorner.y + 15);

	window.draw(_lifesSprite);

	_pointsText.setPosition(viewCorner.x + 15, viewCorner.y + 50); // Ejemplo de posici�n

	window.draw(_pointsText);
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

void Juego::respawn() {
    delete _player;
    spawnPlayer();

}

sf::Vector2f Juego::getCameraPosition()
{
	return _player->getPosition();
}

