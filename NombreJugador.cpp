#include "NombreJugador.h"

NombreJugador::NombreJugador()
{
    _nombreJugadorTexture.loadFromFile("imgs/bgName2.png");
    _nombreJugadorSprite.setTexture(_nombreJugadorTexture);

	_font.loadFromFile("fonts/PixelOperator8.ttf");
}

void NombreJugador::update(sf::Event event)
{
    if (_inNombreJugador && event.type == sf::Event::TextEntered)
    {
        if ((event.text.unicode >= 'a' && event.text.unicode <= 'z') && _nombrejugador.length() < 5)
        {
            _nombrejugador += static_cast<char>(event.text.unicode - 32);
        }
        else if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') && _nombrejugador.length() < 5)
        {
            _nombrejugador += static_cast<char>(event.text.unicode);
        }
        else if (event.text.unicode == 8 && !_nombrejugador.empty())
        {
            _nombrejugador.pop_back();
        }
        else if (event.text.unicode == 13 && !_nombrejugador.empty())
        {
            _setNombreJugador = true;
        }
    }
}

void NombreJugador::render(sf::RenderWindow& window)
{
    sf::View currentView = window.getView();
    sf::Vector2f centerPosition = currentView.getCenter();

    _nombreJugadorSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
    window.draw(_nombreJugadorSprite);

    sf::Text label;
    label.setFont(_font);
    label.setCharacterSize(15);
    label.setFillColor(sf::Color::White);
    label.setOutlineThickness(2);
    label.setOutlineColor(sf::Color::Black);
    label.setString("INGRESA TU NOMBRE:");

    sf::FloatRect textRect = label.getLocalBounds();

    label.setPosition(centerPosition.x - textRect.width / 2 -15, centerPosition.y - textRect.height / 2 - 75);
    window.draw(label);


    sf::Text nombreJugadorText;
    nombreJugadorText.setFont(_font);
    nombreJugadorText.setCharacterSize(24);
    nombreJugadorText.setFillColor(sf::Color::White);
    nombreJugadorText.setOutlineThickness(2);
    nombreJugadorText.setOutlineColor(sf::Color::Black);
    nombreJugadorText.setString(_nombrejugador); // Usamos _nombrejugador para mostrar el nombre actual
    // Calcula el ancho del texto del nombre del jugador
    sf::FloatRect nombreJugadorRect = nombreJugadorText.getLocalBounds();
    // Ajusta la posici�n x para centrar el texto
    nombreJugadorText.setPosition(centerPosition.x - nombreJugadorRect.width / 2 -20, centerPosition.y - nombreJugadorRect.height / 2 - 5);
    window.draw(nombreJugadorText);
}

bool NombreJugador::getInNombreJugador() const
{
	return _inNombreJugador;
}

std::string NombreJugador::getNombreJugador() const
{
	return _nombrejugador;
}

bool NombreJugador::setNombreJugador() const
{
	return _setNombreJugador;
}

void NombreJugador::open()
{
	_inNombreJugador = true;
    _setNombreJugador = false;
    _nombrejugador.clear();
}

void NombreJugador::close()
{
	_inNombreJugador = false;
}
