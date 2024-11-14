#include "Win.h"

Win::Win(){
    _winTexture.loadFromFile("imgs/Win.png");
    _winSprite.setTexture(_winTexture);
    _font.loadFromFile("fonts/PixelOperator8-Bold.ttf");

}
void Win::update(){

}


void Win::render(sf::RenderWindow& window){
sf::View currentView = window.getView();
sf::Vector2f centerPosition = currentView.getCenter();
sf::Vector2f viewSize = currentView.getSize();
sf::Vector2f viewCorner(centerPosition.x - viewSize.x / 2, centerPosition.y - viewSize.y / 2);


    sf::Time elapsed = _clock.getElapsedTime();
    _tiempoRestante = _tiempo - elapsed.asSeconds();
    std::string timerBackwardText = std::to_string(static_cast<int>(_tiempoRestante)) + " s";
    _timerText.setString(timerBackwardText);

    if(_tiempoRestante <= 0){
        _win = false;
    }
    _timerText.setFont(_font);
    _timerText.setCharacterSize(24);
    _timerText.setFillColor(sf::Color::White);
    _timerText.setOutlineThickness(2);
	_timerText.setOutlineColor(sf::Color::Black);


	sf::Text text;
    text.setFont(_font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setString("GANASTE!");

    sf::FloatRect textoRect = text.getLocalBounds();
    text.setOrigin(textoRect.left + textoRect.width / 3.0f, textoRect.top + textoRect.height / 2.0f);
    text.setPosition(centerPosition.x, centerPosition.y);
    _timerText.setPosition(centerPosition.x, centerPosition.y - 50);

    _winSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
    window.draw(_winSprite);
    window.draw(_timerText);
    window.draw(text);

}

bool Win::getWin(){
    return _win;
}

void Win::open()
{
	_win = true;
	_clock.restart();
}

void Win::close()
{
	_win = false;
}
