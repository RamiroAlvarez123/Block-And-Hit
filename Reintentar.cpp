#include "Reintentar.h"

Reintentar::Reintentar()
{
	_yesTexture.loadFromFile("imgs/intento_si.png");
	_yesSprite.setTexture(_yesTexture);

	_noTexture.loadFromFile("imgs/intento_no.png");
	_noSprite.setTexture(_noTexture);
}

void Reintentar::update(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left) {
			_reintentarSelection = (_reintentarSelection + 1) % 2; // Alternates between 0 and
		}
		else if (event.key.code == sf::Keyboard::Right) {
			_reintentarSelection = (_reintentarSelection + 1) % 2; // Alternates between 0 and 1
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			if (_reintentarSelection == 0) {
				_selectedOption = 0;
			}
			else if (_reintentarSelection == 1) {
				_selectedOption = 1;
			}
		}
	}
}

void Reintentar::render(sf::RenderWindow& window)
{
	sf::View currentView = window.getView();
	sf::Vector2f centerPosition = currentView.getCenter();

	if (_reintentarSelection == 0) {
		_yesSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_yesSprite);
	}
	else if (_reintentarSelection == 1) {
		_noSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_noSprite);
	}
}

int Reintentar::getSelectedOption() const
{
	return _selectedOption;
}

bool Reintentar::getReintentar() const
{
	return _reintentar;
}

void Reintentar::open()
{
	_reintentarSelection = 0;
	_selectedOption = -1;
	_reintentar = true;
}

void Reintentar::close()
{
	_reintentar = false;
}
