#pragma once
#include "TiledMap.h"
#include "Structures.h"
#include "Player.h"
#include "EnemySpawn.h"
#include "ScoreboardFile.h"
#include "ObjJugador.h"
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

	int _puntos = 0;
	sf::Font _font;
	sf::Text _pointsText;

    float _tiempo = 240.0f;
    float _tiempoRestante;
    sf::Clock clock;
    sf::Text _timerText;

    Structures* _structures;
    Player* _player;
    EnemySpawn* _enemySpawn;
    ScoreboardFile _scoreboardfile;
    std::string _nombreJugador = "";

	bool _reintentar = false;
	bool _showCredits = false;
    bool _juego = false;
    bool _pausa = false;
    bool _infinish = false;

	bool _isFrozen = false;
	bool _isFadingOut = false;
public:
    Juego(b2World& world);
    IniJugador(const std::string& nombreJugador, int puntos);
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
    void setNombreJugador(std::string nombrejugador);
    std::string getNombreJugador();
    bool getJuego();
    bool getFinish();
    bool getReintentar();
    void crearJuego();
    bool getPausa();
    void close();
    void open();
    sf::Vector2f getCameraPosition();

};
