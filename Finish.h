#pragma once
#include "GlobalContactListener.h"
#include "constants.h"
#include <box2d/box2d.h>
#include <vector>
#include <tmxlite/ObjectGroup.hpp>

class Finish {

private:
	b2Body* _body;

	FixtureData* _fixtureData;
public:
	Finish(b2World& world, b2Vec2 position, float width, float height);

	~Finish();
};

