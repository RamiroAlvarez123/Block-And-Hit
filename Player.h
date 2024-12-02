#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "GlobalContactListener.h"
#include "entities.h"
enum class PlayerState {
	Idle = 0,
	Move,
	Jump,
	Defend,
};

class Player : public Entities{
private:
	sf::Texture _textureShield;
	sf::SoundBuffer _buffer2;
	sf::Sound _jumpS;
	sf::Clock clock;
	sf::Time cooldownWalk = sf::seconds(0.3f);
    sf::Time cooldown = sf::seconds(8.0f);

	b2Vec2 _startingPosition;

	bool _isJumping = false;
	bool _isFalling = false;
	bool _isWalking = false;
	bool _isDucking = false;
	bool _didJump = false;
    bool _isBlocking = false;
    bool _shieldActive = false;
    bool _shieldCooldown = false;
    float _shieldCooldownTime = 2.0f;
    float _shieldTimer = 0.0f;
    float _shieldDuration = 2.0f;

	PlayerState _state = PlayerState::Idle;

	bool _onGround = false;
	bool _finished = false;
	bool _onRoof = false;

	b2Fixture* _groundFixture;
	b2Fixture* _spikeFixture;
	b2Fixture* _finishFixture;
	b2Fixture* _topFixture;
	b2Fixture* _shieldFixture;
public:
	Player(b2World& world, b2Vec2 position);

	~Player();

	sf::Vector2f getPosition();
	void update();
    void activateShield();
    void deactivateShield();

	void cmd();

	bool isDead();
	bool inFinish();
	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void onEndContact(b2Fixture* self, b2Fixture* other) override;
};

