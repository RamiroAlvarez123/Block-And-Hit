#include "RedEnemy.h"
#include <iostream>

RedEnemy::RedEnemy(b2World& world, b2Vec2 position)
{
    _fixtureData.listener = this;
    _fixtureData.redenemy = this;
    _fixtureData.type = FixtureDataType::RedEnemy;

    // Define Body
    b2BodyDef bodyDef;
    bodyDef.position.Set((position.x + _width / 2.0f) / pixels_per_meter, (position.y + _height / 2.0f) / pixels_per_meter);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;

    // Create Body
    _body = world.CreateBody(&bodyDef);

    // Create Shape
    b2PolygonShape b2shape;
    b2shape.SetAsBox(_width / 1.7f / pixels_per_meter, _height / 1.5f / pixels_per_meter);

    // Create Fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &b2shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;

    // Attach Shape to Body
    _body->CreateFixture(&fixtureDef);

    // Create SFML Sprite
    _texture.loadFromFile("imgs/slimeRed.png");
    _sprite = new sf::Sprite();
    _sprite->setTexture(_texture);
    _sprite->setTextureRect({ 27, 33, 18, 16 });
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height / 2.0f);
    _sprite->setScale(-1, 1);

    _body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);
}

RedEnemy::~RedEnemy()
{
    //_body->GetWorld()->DestroyBody(_body);
    if (_body) {
        _body->GetWorld()->DestroyBody(_body);
        _body = nullptr;
    }
}

void RedEnemy::update()
{
    _frame += 0.05f;

    if (_frame > 2) {
        _frame = 0;
    }

    _sprite->setTextureRect({ 0 + (int)_frame * 51, 31, 17, 18 });

    _velocity = _body->GetLinearVelocity();

    if (std::abs(_velocity.x) <= 0.02f) {
        _moveSpeed *= -1.0f;
    }

    if (_velocity.x < 0) {
        _sprite->setScale(-1, 1);
    }
    else if (_velocity.x > 0) {
        _sprite->setScale(1, 1);
    }

    _velocity.x = _moveSpeed;

    _body->SetLinearVelocity(_velocity);


    if (_isHit) {
        _deathTimer += 0.07f;
        _sprite->setTextureRect({ 50, 59, 18, 12 });

        _sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height * -1.0f);

        if (_deathTimer >= 1) {
            //body->SetTransform(b2Vec2(_body->GetPosition().x, 1000.0f / pixels_per_meter), _body->GetAngle());
            _isDead = true;
            _deathTimer = 0.0f;
            return;
        }
    }
}

void RedEnemy::render(sf::RenderWindow& window)
{
    _sprite->setPosition(_body->GetPosition().x * pixels_per_meter, _body->GetPosition().y * pixels_per_meter);
    _sprite->setRotation(_body->GetAngle() * deg_per_rad);
    window.draw(*_sprite);
}

void RedEnemy::onBeginContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;

    if(data->type == FixtureDataType::Player) {
        _isHit = true;
        // Obtiene la posición del escudo (otro objeto)
        b2Vec2 shieldPosition = other->GetBody()->GetPosition();
        b2Vec2 enemyPosition = _body->GetPosition();

        // Aplica un impulso para simular el empuje por el escudo
        b2Vec2 pushForce;

        // Determina la dirección del empuje en función de la posición relativa
        if (shieldPosition.x < enemyPosition.x) { // El escudo está a la izquierda
            pushForce.Set(10.0f, 0.0f);
        } else { // El escudo está a la derecha
            pushForce.Set(-10.0f, 0.0f);
        }

        _body->ApplyLinearImpulseToCenter(pushForce, true);
    }
}

void RedEnemy::onEndContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;
}

bool RedEnemy::isDead() {
    return _isDead;
}
