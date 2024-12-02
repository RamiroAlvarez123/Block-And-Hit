#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "GlobalContactListener.h"
#include "entities.h"
class Enemy : public Entities
{
private:
	int vidas=2;

public:
	Enemy(b2World& world, b2Vec2 position);
	~Enemy();

	void update() override;

	virtual void onBeginContact(b2Fixture* self, b2Fixture* other) override;
	virtual void onEndContact(b2Fixture* self, b2Fixture* other) override;

};


