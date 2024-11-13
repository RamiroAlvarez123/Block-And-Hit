#pragma once
#include <SFML/Graphics.hpp>

class NombreJugador
{
private:
	sf::Texture _nombreJugadorTexture;
	sf::Sprite _nombreJugadorSprite;

	sf::Font _font;

	std::string _nombrejugador = "";

	bool _setNombreJugador = false;
	bool _inNombreJugador = false;
public:
	NombreJugador();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	std::string getNombreJugador() const;

	bool getInNombreJugador() const;

	bool setNombreJugador() const;

	void open();

	void close();
};

