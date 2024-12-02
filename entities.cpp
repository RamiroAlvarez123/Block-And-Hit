#include "entities.h"

BaseEnemy::BaseEnemy(b2World& world, b2Vec2 position, float width, float height, float moveSpeed)
    : _width(width), _height(height), _moveSpeed(moveSpeed),
      _velocity(0.0f, 0.0f), _stateTime(0.0f), _frame(0.0f),
      _isHit(false), _isDead(false), _deathTimer(0.0f) {

}

BaseEnemy::~BaseEnemy() {

}

void BaseEnemy::render(sf::RenderWindow& window) {
	_sprite->setPosition(_body->GetPosition().x * pixels_per_meter, _body->GetPosition().y * pixels_per_meter);
	_sprite->setRotation(_body->GetAngle() * deg_per_rad);
	window.draw(*_sprite);
}

bool BaseEnemy::isDead() const {
    return _isDead;
}
