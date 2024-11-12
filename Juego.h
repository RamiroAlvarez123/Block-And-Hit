#pragma once
#include "TiledMap.h"
#include "Structures.h"
#include "Player.h"
#include "EnemySpawn.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Juego
{

private:
    b2World& _world;
    TiledMap* _tiledMap;

    sf::Sound _sound;
	sf::SoundBuffer _buffer;

    int _lifes = 4;
	sf::Texture _lifesTexture;
	sf::Sprite _lifesSprite;

	int _totalPoints = 0;
	sf::Font _font;
	sf::Text _pointsText;

    Structures* _structures;
    Player* _player;
    EnemySpawn* _enemySpawn;
    std::string _playerName = "";

	bool _reintentar = false;
	bool _showCredits = false;
    bool _juego = false;
    bool _pausa = false;

	sf::RectangleShape* _deathScreen;
	int _deathScreenOpacity = 0;
	bool _isFrozen = false;
	bool _isFadingOut = false;
public:
    Juego(b2World& world);
    ~Juego();
    void update();
    void update(sf::Event event);
    void render(sf::RenderWindow& window);
    void generateMap();
    void generateStructures();
    void spawnPlayer();
    void spawnEnemies();
    void reintentar();
    void respawn();
    bool getJuego();
    bool getReintentar();
    void crearJuego();
    bool getPausa();
    void close();
    void open();
    sf::Vector2f getCameraPosition();

};
