#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "GlobalContactListener.h"

enum class PlayerState {
	Idle = 0,
	Move,
	Jump,
	Defend,
};

class Player : public ContactListener
{
private:

	sf::Texture _texture;
	sf::Texture _textureShield;
	sf::Sprite* _sprite;
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	sf::Clock clock;
	sf::Time cooldownWalk = sf::seconds(0.3f);
	b2Body* _body;

    sf::Time cooldown = sf::seconds(8.0f);
	b2Fixture* _shieldFixture; // Fixture del escudo

	float _width = 3.0f;
	float _height = 32.0f;

	b2Vec2 _startingPosition;

	bool _isJumping = false;
	bool _isFalling = false;
	bool _isWalking = false;
	bool _isDucking = false;
	bool _didJump = false;
    bool _isBlocking = false;
    bool _shieldActive = false;
    bool _shieldCooldown = false;
    float _shieldCooldownTime = 3.0f;
    float _shieldTimer = 0.0f;
    float _shieldDuration = 2.0f;

	b2Vec2 _velocity{ 0.0f , 0.0f };
	float _moveSpeed = 10.0f;

	float _stateTime = 0.0f;

	float _frame = 0.0f;

	PlayerState _state = PlayerState::Idle;

	bool _onGround = false;
	bool _death = false;
	bool _finished = false;
	bool _onRoof = false;

	FixtureData _fixtureData;
	b2Fixture* _groundFixture;
	b2Fixture* _spikeFixture;
	b2Fixture* _finishFixture;
	b2Fixture* _rightEnemyFixture;
	b2Fixture* _leftEnemyFixture;
	b2Fixture* _topFixture;
public:
	Player(b2World& world, b2Vec2 position);

	~Player();

	sf::Vector2f getPosition();

	void update();
    // Métodos para activar y desactivar el escudo
    void activateShield();
    void deactivateShield();
    //
	void render(sf::RenderWindow& window);

	void cmd();

	void drawFixture(b2Fixture* fixture, sf::RenderWindow& window, sf::Color color);
	bool isDead();
	bool inFinish();
	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void onEndContact(b2Fixture* self, b2Fixture* other) override;
};

