#include "Player.h"
#include <iostream>

Player::Player(b2World& world, b2Vec2 position) : Entities(3.0f, 32.0f, 10.0f){
	_fixtureData.listener = this;
	_fixtureData.player = this;
	_fixtureData.type = FixtureDataType::Player;

	// Define Body
	b2BodyDef bodyDef;
	bodyDef.position.Set((position.x + _width / 2.0f) / pixels_per_meter, (position.y + _height / 2.0f) / pixels_per_meter);
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;

	// Create Body
	_body = world.CreateBody(&bodyDef);

	// Create Shape
	b2PolygonShape b2shape;
	b2shape.SetAsBox(_width / 2.0f / pixels_per_meter, _height / 2.0f / pixels_per_meter);

	// Create Fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &b2shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
	_spikeFixture = _body->CreateFixture(&fixtureDef);


	// Attach Shape to Body
	_body->CreateFixture(&fixtureDef);

	// Sensor de colisiones para que no se ejecute el salto en bordes de paredes
	b2shape.SetAsBox(0.3f, 0.2f, b2Vec2(0.0f, 1.0f), 0.0f);
	fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
	fixtureDef.isSensor = true;
	_groundFixture = _body->CreateFixture(&fixtureDef);

	b2shape.SetAsBox(0.4f, 0.1f, b2Vec2(-0.0f, -0.8f), 0.0f);
	fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
	fixtureDef.isSensor = true;
	_topFixture = _body->CreateFixture(&fixtureDef);

	_texture.loadFromFile("imgs/knight.png");
	_textureShield.loadFromFile("imgs/shield.png");
	_sprite = new sf::Sprite();
	_sprite->setTexture(_texture);
	_sprite->setTextureRect({ 7, 7 , 20, 22 });
	_sprite->setOrigin(_sprite->getGlobalBounds().width / 2.0f, _sprite->getGlobalBounds().height / 2.0f);
	_sprite->setScale(1, 1);
	_shieldFixture == nullptr;

	_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(_sprite);
}

Player::~Player()
{
	_body->GetWorld()->DestroyBody(_body);
}

void Player::cmd()
{
	bool isMoving = false;


if(!_shieldActive){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_velocity.x = _moveSpeed;
		_state = PlayerState::Move;
		isMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_velocity.x = -_moveSpeed;
		_state = PlayerState::Move;

		isMoving = true;
	}
	if (!_didJump) {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))&& _onGround) {
            _buffer.loadFromFile("sounds/jump.wav");
			_jumpS.setBuffer(_buffer);
			_jumpS.play();
			_didJump = true;
			_isJumping = true;
			isMoving = true;
			_velocity.y += -17.0f;
			_sprite->setTextureRect({ 6, 71, 23, 20 });
			_state = PlayerState::Jump;
		}
	}

}

if(_shieldTimer <= 0.8f && !_didJump){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		_state = PlayerState::Defend;
		isMoving = true;
	}
}


	if (_didJump) {

		if (_velocity.y > -25.0f && _isJumping) {
			_velocity.y += -1.0f;
			if (_velocity.y <= -25.0f) {
				_isJumping = false;
				_isFalling = true;
				isMoving = true;
			}

		}
		if (_isFalling) {
			_velocity.y += 1.0f;
			isMoving = true;
			_sprite->setTextureRect({ 6, 71, 23, 22 });
			if (_velocity.y == 0) {
				_didJump = false;
				_isJumping = false;
				_isFalling = false;
			}

			else if (_onRoof) {
				_velocity.y = -5.0f;
				_sprite->setTextureRect({ 6, 71, 23, 22 });
				_didJump = false;
				_isJumping = false;
				_isFalling = false;
				_onGround = false;
			}

		}
	}

	if (!isMoving) {
		_state = PlayerState::Idle;
	}

}

void Player::update()
{
    if (_shieldActive) {
        _shieldTimer += 0.026f;  // Asumiendo que update se llama a ~60 FPS
        if (_shieldTimer >= _shieldDuration) {
            deactivateShield();  // Desactiva el escudo después de la duración
            _shieldTimer = 0.0f; // Reinicia el temporizador
        }
    }

    if (_shieldCooldown) {

        _shieldTimer += 0.016f;  // Asumiendo que update se llama a ~60 FPS
        if (_shieldTimer >= _shieldCooldownTime) {

            _shieldCooldown = false;  // Finaliza el cooldown
            _shieldTimer = 0.0f;      // Reinicia el temporizador
            std::cout << "Escudo listo para ser activado nuevamente." << std::endl;
        }
    }

	switch (_state) {
	case PlayerState::Idle:
		_sprite->setTexture(_texture);
		_sprite->setTextureRect({ 7, 7, 23, 30 });
		_sprite->setOrigin(3.5f, 4.0f);
		break;
	case PlayerState::Move:
		_sprite->setTexture(_texture);
		_frame += 0.2f;

		if (_frame > 3) _frame = 0;

		_sprite->setTextureRect({ 6 + int(_frame) * 33, 66, 24, 25 });
		_sprite->setOrigin(3.0f, 8.5f);

		if (_velocity.x < 0) _sprite->setScale(-1, 1);
		else if (_velocity.x > 0) _sprite->setScale(1, 1);
		//deactivateShield();
		break;

    case PlayerState::Defend:
		if (_velocity.x < 0) _sprite->setScale(-1, 1);
		else if (_velocity.x > 0) _sprite->setScale(1, 1);
		activateShield();
		_sprite->setOrigin(5.0f, 2.0f);
		break;
	}


	// Ajustar el fixture según la textura
    b2PolygonShape shape;
    shape.SetAsBox((_sprite->getGlobalBounds().width / 2.f) / pixels_per_meter, (_sprite->getGlobalBounds().height / 1.85f) / pixels_per_meter);
    _body->DestroyFixture(_spikeFixture); // Elimina el fixture anterior
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData.pointer = (uintptr_t)&_fixtureData;
    _spikeFixture = _body->CreateFixture(&fixtureDef); // Crea un nuevo fixture actualizado

	_body->SetLinearVelocity(_velocity);
	_velocity.x = 0.0f;


}


sf::Vector2f Player::getPosition() {
	b2Vec2 pos = _body->GetPosition();
	return sf::Vector2f(pos.x * pixels_per_meter, pos.y * pixels_per_meter);
}

void Player::onBeginContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

	if (!data) {
		return;
	}

	if (_spikeFixture == self && data->type == FixtureDataType::Spike) {
		_isDead = true;
	}
	if (data->type == FixtureDataType::Finish) {
		_finished = true;
	}
	else if (_groundFixture == self && (data->type == FixtureDataType::GroundTile)) {
		_onGround = true;
	}
	else if (self == _topFixture && (data->type == FixtureDataType::GroundTile)) {
		_onRoof = true;
	}
    if ((data->type == FixtureDataType::Enemy || data->type == FixtureDataType::RedEnemy) && (_state != PlayerState::Defend || _shieldFixture == nullptr)) {
        _isDead = true;
    }

     if (_sprite->getPosition().y >= 430){
        _isDead = true;
        }
}

void Player::onEndContact(b2Fixture* self, b2Fixture* other)
{
	FixtureData* data = (FixtureData*)other->GetUserData().pointer;

		if (!data) {
		return;
	}

	else if (self == _topFixture && data->type == FixtureDataType::GroundTile) {
		_onRoof = false;
	}
	else if (_groundFixture == self && (data->type == FixtureDataType::GroundTile)) {
		_onGround = false;
	}

	if (_shieldFixture != nullptr && self == _shieldFixture && data->type == FixtureDataType::Enemy && _state == PlayerState::Defend) {
        b2Body* enemyBody = other->GetBody();

        // Calcular el empuje en función de la orientación del sprite
        float pushForceX = (_sprite->getScale().x > 0) ? 10.0f : -10.0f;
        b2Vec2 pushForce(pushForceX, 0.0f);


        // Aplicar impulso al enemigo en la dirección correcta
        enemyBody->ApplyLinearImpulseToCenter(pushForce, true);
    }

}

void Player::activateShield() {
    if (!_shieldCooldown && !_shieldActive) {// Solo activa si el escudo no está en cooldown

        _sprite->setTexture(_textureShield);
		_sprite->setTextureRect({ 5, 4, 26, 19 });
        b2PolygonShape shieldShape;
        shieldShape.SetAsBox(0.3f, 0.5f, b2Vec2(0.6f, 0.0f), 0.0f);

        b2FixtureDef shieldFixtureDef;
        shieldFixtureDef.shape = &shieldShape;
        shieldFixtureDef.isSensor = true;

        FixtureData* shieldFixtureData = new FixtureData();
        shieldFixtureData->type = FixtureDataType::PlayerShield;
        shieldFixtureData->listener = this;
        shieldFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(shieldFixtureData);

        _shieldFixture = _body->CreateFixture(&shieldFixtureDef);
        _shieldActive = true;
        _shieldCooldown = true;  // Inicia el cooldown después de activar
        _shieldTimer = 0.0f;     // Reinicia el temporizador

    }

}

void Player::deactivateShield() {
    _buffer2.loadFromFile("sounds/charging.wav");
    _sound.setBuffer(_buffer2);
    _sound.play();
    if (_shieldFixture != nullptr) {
        //std::cout << "Desactivando escudo" << std::endl;
        _body->DestroyFixture(_shieldFixture);
        _shieldFixture = nullptr;
        _shieldActive = false;
    }
}


bool Player::isDead() {
	return _isDead;
}

bool Player::inFinish(){
    return _finished;
}
