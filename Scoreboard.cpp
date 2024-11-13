#include <iostream>
#include "Scoreboard.h"


Scoreboard::Scoreboard(){
_topTexture.loadFromFile("imgs/top10.jpg");  /// agregar imagen de ranking top10
_topSprite.setTexture(_topTexture);

}

void Scoreboard::update(sf::Event event){

if(event.type == sf::Event::KeyPressed){
    if (event.key.code == sf::Keyboard::Escape) {
			_SelectOpc = 2;
		}
 }

}

void Scoreboard::render(sf::RenderWindow& window){

	sf::View currentView=window.getView();
	sf::Vector2f centerPosition = currentView.getCenter();

    _topSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
    window.draw(_topSprite);
    _scoreboardfile.mostrarTop(window);

}

	bool Scoreboard::getScoreboard() const{
	return _inScoreboard;
	}

	void Scoreboard::open(){
	 _scoreboardfile.ordenarRanking();
	_SelectOpc = -1;
	_inScoreboard = true;
	}

	void Scoreboard::close(){
		_inScoreboard = false;
	}

	int Scoreboard::getSelectOpc() const{
	return _SelectOpc;
	}
