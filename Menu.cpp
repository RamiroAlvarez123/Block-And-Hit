#include <iostream>
#include "Menu.h"


Menu::Menu(){
    _menuSelecOpc = 0;
     _menuSelectedOpc = -1;
     _inMenu = true;

	_jugarTexture.loadFromFile("imgs/menu_jugar.jpg");
	_jugarSprite.setTexture(_jugarTexture);

    _rankTexture.loadFromFile("imgs/menu_scoreboard.jpg");
	_rankSprite.setTexture(_rankTexture);

	_salirTexture.loadFromFile("imgs/menu_salir.jpg");
	_salirSprite.setTexture(_salirTexture);
};

void Menu::update(sf::Event event){

if(event.type== sf::Event::KeyPressed){
    if(event.key.code==sf::Keyboard::Left){

       _menuSelecOpc=(_menuSelecOpc+1) %3;
    }
    else if(event.key.code==sf::Keyboard::Right){
        _menuSelecOpc=(_menuSelecOpc+2) %3;
    }
    else if (event.key.code == sf::Keyboard::Enter) {
        if(_menuSelecOpc==0){
            _menuSelectedOpc=0;
        }
        else if(_menuSelecOpc==1){
            _menuSelectedOpc=1;
        }
        else if(_menuSelecOpc==2){
            _menuSelectedOpc=2;
        }
    }
}

}
void Menu::render(sf::RenderWindow& window){
sf::View currentView = window.getView();
	sf::Vector2f centerPosition = currentView.getCenter();

	if (_menuSelecOpc == 0) {
		_jugarSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_jugarSprite);
	}
	else if (_menuSelecOpc == 1) {
        _rankSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_rankSprite);
	}
	else if (_menuSelecOpc == 2) {
		_salirSprite.setPosition(centerPosition.x - 400.0f, 0.0f);
		window.draw(_salirSprite);
	}
}
bool Menu::getMenu() const{
return _inMenu;
}
bool Menu::getSalida() const{
if (_menuSelectedOpc == 2) {

		return true;
	}
	return false;
}
void Menu::open(){
	_menuSelecOpc = 0;
	_menuSelectedOpc = -1;
	_inMenu = true;
}
void Menu::close(){
	_inMenu = false;
	}
int Menu::getSelectedOpc() const{
return _menuSelectedOpc;
}
