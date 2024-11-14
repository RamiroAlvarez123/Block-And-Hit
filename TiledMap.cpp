#include "TiledMap.h"
#include <iostream>

TiledMap::TiledMap(b2World& world) : _world(world)
{
	if (_map.load("Tiled/Mapa.tmx"))
	{
		loadBackground();
		loadTilesets();
	}
	else
	{
		std::cerr << "Failed to load map" << std::endl;
	}
}

void TiledMap::loadBackground() {
	const auto& layers = _map.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Image)
		{
			const auto& imageLayer = layer->getLayerAs<tmx::ImageLayer>();
			if (imageLayer.getName() == "Montaña") {
				if (!_MontTexture.loadFromFile("imgs/Montania.png"))
				{
					std::cerr << "Failed to load image layer" << std::endl;
					continue;
				}
				// Habilitar la repetici�n de la textura en el eje X (y Y si es necesario)
				_MontTexture.setRepeated(true);

				_MontSprite.setTexture(_MontTexture);
                _MontSprite.setTextureRect(sf::IntRect(0, 0, _MontTexture.getSize().x * 20, _MontTexture.getSize().y));

				_MontSprite.setPosition(imageLayer.getOffset().x, imageLayer.getOffset().y);
			}
			else if (imageLayer.getName() == "Extension") {
				if (!_ExtTexture.loadFromFile("imgs/Extension.png"))
				{
					std::cerr << "Failed to load image layer" << std::endl;
					continue;
				}

				_ExtTexture.setRepeated(true);

				_ExtSprite.setTexture(_ExtTexture);
                _ExtSprite.setTextureRect(sf::IntRect(0, 0, _ExtTexture.getSize().x * 10, _ExtTexture.getSize().y));
				_ExtSprite.setPosition(imageLayer.getOffset().x, imageLayer.getOffset().y);
			}
			else if (imageLayer.getName() == "Cielo") {
				if (!_CieloTexture.loadFromFile("imgs/Cielo.jpg"))
				{
					std::cerr << "Failed to load image layer" << std::endl;
					continue;
				}

				_CieloTexture.setRepeated(true);

				_CieloSprite.setTexture(_CieloTexture);
                _CieloSprite.setTextureRect(sf::IntRect(0, 0, _CieloTexture.getSize().x * 6, _CieloTexture.getSize().y));

				_CieloSprite.setPosition(imageLayer.getOffset().x, imageLayer.getOffset().y);
			}
			else if (imageLayer.getName() == "Cueva") {
				if (!_CuevaTexture.loadFromFile("imgs/cueva2.png"))
				{
					std::cerr << "Failed to load image layer" << std::endl;
					continue;
				}




				_CuevaSprite.setTexture(_CuevaTexture);
                _CuevaSprite.setTextureRect(sf::IntRect(0, 0, _CuevaTexture.getSize().x, _CuevaTexture.getSize().y));

				_CuevaSprite.setPosition(imageLayer.getOffset().x, imageLayer.getOffset().y);
			}
		}
	}

}

b2Vec2 TiledMap::getPlayerSpawnPoint()
{
	const auto& layers = _map.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			const auto& objects = objectLayer.getObjects();
			for (const auto& object : objects)
			{
				tmx::Object::Shape shape = object.getShape();

				if (shape == tmx::Object::Shape::Point) {
					if (object.getName() == "Player") {
						tmx::Vector2f position = object.getPosition();
						return b2Vec2(position.x, position.y);
					}
				}
			}
		}
	}
}

bool TiledMap::loadTilesets()
{
    // Define los tilesets y sus rutas
    std::vector<std::pair<int, std::string>> tilesetPaths = {
        {1, "Tiled/tiles/Tileset.png"},
        {49, "Tiled/tiles/Decors.png"},
        {147, "Tiled/tiles/Tileset2.png"}
    };

    for (const auto& tilesetInfo : tilesetPaths)
    {
        Tileset tileset;
        if (!tileset.texture.loadFromFile(tilesetInfo.second))
        {
            std::cerr << "Error cargando el tileset: " << tilesetInfo.second << std::endl;

            return false;
        }
        tileset.firstgid = tilesetInfo.first;
        _tilesets.push_back(tileset);
    }

    return true;
}

void TiledMap::render(sf::RenderWindow& window)
{

	window.draw(_CieloSprite);
	window.draw(_MontSprite);
	window.draw(_ExtSprite);
    window.draw(_CuevaSprite);

	const int tileSize = 16;

	for (const auto& layer : _map.getLayers())
	{
		if (layer->getType() == tmx::Layer::Type::Tile)
		{
			// Use tileLayer data to render tiles or setup physics.
			const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
			const auto& tiles = tileLayer.getTiles();

			for (unsigned int y = 0; y < tileLayer.getSize().y; ++y)
			{
				for (unsigned int x = 0; x < tileLayer.getSize().x; ++x)
				{
					int globalTileID = tiles[y * tileLayer.getSize().x + x].ID;
					if (globalTileID == 0) continue;

					Tileset* currentTileset = nullptr;
                    int localTileID = globalTileID;

					for (auto& tileset : _tilesets)
                    {
                        if (globalTileID >= tileset.firstgid)
                        {
                            currentTileset = &tileset;
                            localTileID = globalTileID - tileset.firstgid;
                        }
                    }
                    if (!currentTileset) continue;

					sf::Vector2u textureSize = currentTileset->texture.getSize();
					int tu = localTileID % (textureSize.x / tileSize);
					int tv = localTileID / (textureSize.x / tileSize);

					sf::Sprite sprite;
					sprite.setTexture(currentTileset->texture);
					sprite.setTextureRect(sf::IntRect(tu * tileSize, tv * tileSize, tileSize, tileSize));
					sprite.setPosition(x * tileSize, y * tileSize);

					window.draw(sprite);
				}
			}
		}
	}

}

tmx::Map& TiledMap::getMap()
{
	return _map;
}
