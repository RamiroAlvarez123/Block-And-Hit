#include "Finish.h"
Finish::Finish(b2World& world, b2Vec2 position, float width, float height)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set((position.x + width / 2.0f) / pixels_per_meter, (position.y + height / 2.0f) / pixels_per_meter);
	bodyDef.type = b2_staticBody;

	_body = world.CreateBody(&bodyDef);

	b2PolygonShape b2shape;
	b2shape.SetAsBox(width / 2.0f / pixels_per_meter, height / 2.0f / pixels_per_meter);

	_fixtureData = new FixtureData();
	_fixtureData->type = FixtureDataType::Finish;

	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)(_fixtureData);
	fixtureDef.shape = &b2shape;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;

	_body->CreateFixture(&fixtureDef);
}

Finish::~Finish()
{
	_body->GetWorld()->DestroyBody(_body);
}
