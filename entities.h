#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "GlobalContactListener.h"

class Entities : public ContactListener {
protected:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;

    sf::Texture _texture;
    sf::Sprite* _sprite;
    b2Body* _body;

    float _width;
    float _height;

    b2Vec2 _velocity;
    float _moveSpeed;

    float _stateTime = 0.0f;
    float _frame = 0.0f;

    FixtureData _fixtureData;

    bool _isHit = false;
    bool _isDead = false;
    float _deathTimer = 0.0f;

public:
    Entities(float width, float height, float moveSpeed);
    virtual ~Entities();

    virtual void update() = 0;
    void render(sf::RenderWindow& window);
    bool isDead() const;
    virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override = 0;
    virtual void onEndContact(b2Fixture* self, b2Fixture* other) override = 0;
};
