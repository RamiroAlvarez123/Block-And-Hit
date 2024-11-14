#pragma once
#include <vector>
#include <box2d/box2d.h>
#include "RedEnemy.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

class RedEnemySpawn
{
private:
	b2World& _world;
	tmx::Map& _tiled;

	std::vector<RedEnemy*> _redenemies;
public:
	RedEnemySpawn(b2World& world, tmx::Map& tiled);

	~RedEnemySpawn();

	void spawnEnemies();
	std::vector<RedEnemy*>& getEnemies();
};
