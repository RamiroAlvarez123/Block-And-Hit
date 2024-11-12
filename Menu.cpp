#include <iostream>
#include "Menu.h"


Menu::Menu(){
    bool _menuOpc = -1;
int _menuSelecOpc = 0;
int _inMenu = true;
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
            _menuOpc=0;
        }
        else if(_menuSelecOpc==1){
            _menuOpc=1;
        }
        else if(_menuSelecOpc==2){
            _menuOpc=2;
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
if (_menuOpc == 2) {
		return true;
	}
	return false;
}
void Menu::open(bool music){
if (!music) {
		Musicmenu.play();
	}
	_menuSelecOpc = 0;
	_menuOpc = -1;
	_inMenu = true;
}
void Menu::close(bool music){
if (!music) {
		Musicmenu.stop();
	}
	_inMenu = false;
	}
int Menu::getSelectedOpc() const{
return _menuOpc;
}
