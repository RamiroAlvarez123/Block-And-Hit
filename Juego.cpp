#include "Juego.h"
#include <iostream>

Juego::Juego(b2World& world) : _world(world)
{
    _tiempo = 240.0f;
    generateMap();
    generateStructures();
    spawnPlayer();
    spawnEnemies();
    _lifesTexture.loadFromFile("imgs/vidas.png");
	_lifesSprite.setTexture(_lifesTexture);

	_font.loadFromFile("fonts/PixelOperator8.ttf");
	_pointsText.setFont(_font);
	_pointsText.setCharacterSize(24);
	_pointsText.setFillColor(sf::Color::White);
	_pointsText.setOutlineThickness(2);
	_pointsText.setOutlineColor(sf::Color::Black);

    _timerText.setFont(_font);
    _timerText.setCharacterSize(24);
    _timerText.setFillColor(sf::Color::White);
    _timerText.setOutlineThickness(2);
	_timerText.setOutlineColor(sf::Color::Black);
}
Juego::~Juego()
{
	delete _tiledMap;
	delete _structures;
	delete _player;
	delete _enemySpawn;
	delete _redEnemySpawn;
}

void Juego::update(){
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

    _pointsText.setString(std::to_string(_puntos) + " PTS");



    if(_player->isDead()){
        _buffer.loadFromFile("sounds/explosion.wav");
        _sound.setBuffer(_buffer);
        _sound.play();
        respawn();

        _lifes--;
        if(_lifes < 1){
            _reintentar = true;
        }
    }



    if(_player->inFinish()){
        _puntos = (_lifes * 200) + _puntos + _tiempoRestante;
        _scoreboardfile.guardarJugador(ObjJugador(getNombreJugador(), _puntos));
        _infinish = true;

    }

    auto& enemies = _enemySpawn->getEnemies();
	for (auto enemy : enemies) {
		enemy->update();
		if (enemy->isDead()) {
            _puntos += 200;
			enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
			delete enemy;
		}
	}

	auto& redenemies = _redEnemySpawn->getEnemies();
	for (auto renemy : redenemies) {
		renemy->update();
		if (renemy->isDead()) {
            _puntos += 300;
			redenemies.erase(std::remove(redenemies.begin(), redenemies.end(), renemy), redenemies.end());
			delete renemy;
		}
	}


}
void Juego::update(sf::Event event){
if(event.key.code==sf::Keyboard::Escape){
        _pausa = true;
    }
}
bool Juego::getPausa(){return _pausa;}

void Juego::render(sf::RenderWindow& window){
    sf::View view = window.getView();
	sf::Vector2f playerPos = getCameraPosition();
	playerPos.x += 150;
	playerPos.y = (float(640) / 2.7);
	view.setCenter(playerPos);
	window.setView(view);

    _tiledMap->render(window);

    _player->render(window);

    sf::Time elapsed = clock.getElapsedTime();
    _tiempoRestante = _tiempo - elapsed.asSeconds();
    std::string timerBackwardText = std::to_string(static_cast<int>(_tiempoRestante)) + " s";
    _timerText.setString(timerBackwardText);

    if(_tiempoRestante <= 0){
        _reintentar = true;
    }

    auto& enemies = _enemySpawn->getEnemies();
	for (auto enemy : enemies) {
		enemy->render(window);
	}

	auto& redenemies = _redEnemySpawn->getEnemies();
	for (auto renemy : redenemies) {
		renemy->render(window);
	}


    sf::Vector2f viewCorner = window.mapPixelToCoords(sf::Vector2i(0, 0), view);
	_lifesSprite.setPosition(viewCorner.x + 15, viewCorner.y);

	window.draw(_lifesSprite);

	_pointsText.setPosition(viewCorner.x + 15, viewCorner.y + 70);
    _timerText.setPosition(viewCorner.x + 300, viewCorner.y + 20);

	window.draw(_pointsText);
    window.draw(_timerText);

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
void Juego::spawnEnemies(){
    _enemySpawn = new EnemySpawn(_world, _tiledMap->getMap());
    _redEnemySpawn = new RedEnemySpawn(_world, _tiledMap->getMap());
}
void Juego::respawn() {
    if(_lifes >1){
    delete _player;
    spawnPlayer();

    }
    delete _enemySpawn;
    delete _redEnemySpawn;
	spawnEnemies();
}
void Juego::reintentar(){
    _reintentar = false;
    _puntos = 0;
    _lifes = 4;
    _tiempo = 240.0f;
    respawn();
}

void Juego::setNombreJugador(std::string nombrejugador){
    _nombreJugador = nombrejugador;
}
std::string Juego::getNombreJugador(){return _nombreJugador;}
int Juego::getPuntos(){ return _puntos;}
bool Juego::getJuego(){ return _juego;}
bool Juego::getFinish(){return _infinish;}
bool Juego::getReintentar(){return _reintentar;}
void Juego::close(){ _juego = false;}
void Juego::open(){ _juego = true, _pausa = false;;}
sf::Vector2f Juego::getCameraPosition()
{
	return _player->getPosition();
}

