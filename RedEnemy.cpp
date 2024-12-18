#include "RedEnemy.h"
#include <iostream>

RedEnemy::RedEnemy(b2World& world, b2Vec2 position)
 : Entities(18.0f, 10.0f, 5.0f){
    _fixtureData.listener = this;
    _fixtureData.redenemy = this;
    _fixtureData.type = FixtureDataType::RedEnemy;

    // Define Body
    b2BodyDef bodyDef;
    bodyDef.position.Set((position.x + _width / 2.0f) / pixels_per_meter, (position.y + _height / 1.8f) / pixels_per_meter);
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

RedEnemy::~RedEnemy(){
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

    // Actualiza el sprite de animación solo si el enemigo no ha sido golpeado
    if (!_isHit) {
        _sprite->setTextureRect({ 0 + (int)_frame * 51, 31, 17, 18 });
    }

    // Si el enemigo no está marcado como "muerto", continúa su movimiento
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

        _deathTimer += 0.07f;
        _sprite->setTextureRect({ 50, 59, 18, 12 });

        if (_deathTimer >= 1) {
            //body->SetTransform(b2Vec2(_body->GetPosition().x, 1000.0f / pixels_per_meter), _body->GetAngle());
            _isDead = true;
            _deathTimer = 0.0f;
            return;
        }
    }
}

void RedEnemy::onBeginContact(b2Fixture* self, b2Fixture* other)
{
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;

    // Detecta si el fixture con el que colisiona es el escudo del jugador
    if (data->type == FixtureDataType::Player) {
        _isHit = true;  // Marca al enemigo como golpeado

        // Obtiene la posición del escudo (otro objeto)
        b2Vec2 shieldPosition = other->GetBody()->GetPosition();
        b2Vec2 RedEnemyPosition = _body->GetPosition();

        // Aplica un impulso para simular el empuje por el escudo
        b2Vec2 pushForce;

        // Determina la dirección del empuje en función de la posición relativa
        if (shieldPosition.x < RedEnemyPosition.x) { // El escudo está a la izquierda
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


