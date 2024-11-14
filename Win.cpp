#include "Win.h"

Win::Win() {
    _winTexture.loadFromFile("imgs/Win.png");
    _winSprite.setTexture(_winTexture);
    _font.loadFromFile("fonts/PixelOperator8-Bold.ttf");

}

void Win::update(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape){
		_selected = 0;
        }
	}
}

void Win::render(sf::RenderWindow& window) {
    sf::View currentView = window.getView();
    sf::Vector2f centerPosition = currentView.getCenter();
    sf::Vector2f viewSize = currentView.getSize();
    sf::Vector2f viewCorner(centerPosition.x - viewSize.x / 2, centerPosition.y - viewSize.y / 2);

    // Texto de victoria
    sf::Text text;
    text.setFont(_font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
    text.setString("GANASTE!");

    sf::Text cont;
    cont.setFont(_font);
    cont.setCharacterSize(24);
    cont.setFillColor(sf::Color::White);
    cont.setOutlineThickness(2);
    cont.setOutlineColor(sf::Color::Black);
    cont.setString("PRESIONA ESCAPE PARA SALIR");

    sf::FloatRect textoRect = text.getLocalBounds();
    text.setOrigin(textoRect.left + textoRect.width / 3.0f, textoRect.top + textoRect.height / 2.0f);
    text.setPosition(centerPosition.x, centerPosition.y);
    cont.setOrigin(textoRect.left + textoRect.width, textoRect.top + textoRect.height);
    cont.setPosition(centerPosition.x - 40, centerPosition.y + 100);

    _winSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
    window.draw(_winSprite);
    window.draw(cont);
    window.draw(text);
}

bool Win::getWin() {
    return _win;
}
int Win::getSelected(){
    return _selected;
}

void Win::open() {
    _selected = -1;
    _win = true;
}

void Win::close() {
    _win = false;
}
