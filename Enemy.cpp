#include "Enemy.h"
#include <iostream>

Enemy::Enemy(b2World& world, b2Vec2 position)
{
    _fixtureData.listener = this;
    _fixtureData.enemy = this;
    _fixtureData.type = FixtureDataType::Enemy;

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
    _texture.loadFromFile("imgs/slime.png");
    _sprite = new sf::Sprite();
    _sprite->setTexture(_texture);
    _sprite->setTextureRect({ 27, 33, 18, 16 });
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height / 2.0f);
    _sprite->setScale(-1, 1);

    _body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);


}

Enemy::~Enemy()
{
    if (_body) {
        _body->GetWorld()->DestroyBody(_body);
        _body = nullptr;
    }
}

void Enemy::update()
{
    _frame += 0.05f;

    if (_frame > 2) {
        _frame = 0;
    }

    // Actualiza el sprite de animaci�n solo si el enemigo no ha sido golpeado
    if (!_isHit) {
        _sprite->setTextureRect({ 0 + (int)_frame * 51, 31, 17, 18 });
    }

    // Si el enemigo no est� marcado como "muerto", contin�a su movimiento
    if (!_isDead) {
        _velocity = _body->GetLinearVelocity();

        if (std::abs(_velocity.x) <= 0.02f) {
            _moveSpeed *= -1.0f;
        }

        if (_velocity.x < 0) {
            _sprite->setScale(-1, 1);
        } else if (_velocity.x > 0) {
            _sprite->setScale(1, 1);
        }

        _velocity.x = _moveSpeed;
        _body->SetLinearVelocity(_velocity);
    }

    // Si el enemigo es golpeado, inicia el temporizador de muerte y actualiza su sprite
    if (_isHit) {

    _buffer.loadFromFile("sounds/hit.wav");
        _sound.setBuffer(_buffer);
        _sound.play();

    if (vidas > 0) {
        vidas -= 1;  // Reduce las vidas
        _sprite->setTextureRect({ 53, 59, 14, 12 });
        _isHit = false; // Resetea el estado de golpe para evitar el decremento continuo

    } else if (vidas <= 0) {
        // Cambia el sprite y empieza el temporizador de muerte
        _sprite->setTextureRect({ 53, 59, 14, 12 });
        _deathTimer += 0.07f;

        // Despu�s de un tiempo, marca al enemigo como muerto
        if (_deathTimer >= 1.0f) {
            _isDead = true;
            _deathTimer = 0.0f;
            return;
        }
    }
}
}

void Enemy::render(sf::RenderWindow& window)
{
    _sprite->setPosition(_body->GetPosition().x * pixels_per_meter, _body->GetPosition().y * pixels_per_meter);
    _sprite->setRotation(_body->GetAngle() * deg_per_rad);
    window.draw(*_sprite);
}

void Enemy::onBeginContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;

    // Detecta si el fixture con el que colisiona es el escudo del jugador
    if (data && data->type == FixtureDataType::PlayerShield) {
        _isHit = true;  // Marca al enemigo como golpeado

        // Obtiene la posici�n del escudo (otro objeto)
        b2Vec2 shieldPosition = other->GetBody()->GetPosition();
        b2Vec2 enemyPosition = _body->GetPosition();

        // Aplica un impulso para simular el empuje por el escudo
        b2Vec2 pushForce;

        // Determina la direcci�n del empuje en funci�n de la posici�n relativa
        if (shieldPosition.x < enemyPosition.x) { // El escudo est� a la izquierda
            pushForce.Set(10.0f, 0.0f);
        } else { // El escudo est� a la derecha
            pushForce.Set(-10.0f, 0.0f);
        }

        _body->ApplyLinearImpulseToCenter(pushForce, true);
    }
}
void Enemy::onEndContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;
    // Puedes a�adir m�s l�gica aqu� si necesitas detectar cu�ndo termina una colisi�n
}

bool Enemy::isDead() {
    return _isDead;
}
