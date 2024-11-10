#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "GlobalContactListener.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/ImageLayer.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <vector>

struct Tileset
{
    sf::Texture texture;
    int firstgid;
};
class TiledMap
{
private:
    b2World& _world;

    tmx::Map _map;
    std::vector<Tileset> _tilesets;

    sf::Texture _MontTexture;
    sf::Sprite _MontSprite;
    sf::Texture _ExtTexture;
    sf::Sprite _ExtSprite;
    sf::Texture _CieloTexture;
    sf::Sprite _CieloSprite;
public:
    TiledMap(b2World& world);

    void render(sf::RenderWindow& window);

    void loadBackground();

    bool loadTilesets();

    b2Vec2 getPlayerSpawnPoint();

    tmx::Map& getMap();
};
