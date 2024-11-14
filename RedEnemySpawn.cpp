#pragma once
#include "RedEnemySpawn.h"

RedEnemySpawn::RedEnemySpawn(b2World& world, tmx::Map& tiled) : _world(world), _tiled(tiled)
{
	spawnEnemies();
}

RedEnemySpawn::~RedEnemySpawn()
{
for (auto enemy : _redenemies) {
		delete enemy;
	}
	_redenemies.clear();
}

void RedEnemySpawn::spawnEnemies()
{

	const auto& layers = _tiled.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();
			for (const auto& object : objects)
			{
				tmx::Object::Shape shape = object.getShape();

				if (object.getName() == "Enemy2") {
					if (shape == tmx::Object::Shape::Point) {
						tmx::Vector2f position = object.getPosition();
						_redenemies.push_back(new RedEnemy(_world, b2Vec2(position.x, position.y + 12.0f)));
					}
				}
			}
		}
	}
}

std::vector<RedEnemy*>& RedEnemySpawn::getEnemies() {
	return _redenemies;
}
