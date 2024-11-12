#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pausa.h"

Pausa::Pausa() {

    _continuarTexture.loadFromFile("imgs/pausa_continuar.png");
    _continuarSprite.setTexture(_continuarTexture);

    _salirTexture.loadFromFile("imgs/pausa_salir.png");
    _salirSprite.setTexture(_salirTexture);

}

// M�todos para dibujar el texto en la ventana

void Pausa::update(sf::Event event) {
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up){
            _seleccion = (_seleccion + 1) % 2;
        }
        if(event.key.code == sf::Keyboard::Down){
            _seleccion = (_seleccion + 1) % 2;
        }else if (event.key.code == sf::Keyboard::Enter){
            if (_seleccion == 0){
            _selectedOpc = 0;
            }else if (_seleccion == 1){
            _selectedOpc = 1;
            }

        }
    }

    // Restaura la vista original (para que el juego contin�e normalmente)


}

void Pausa::render(sf::RenderWindow& window){

    // Guarda la vista original (de la c�mara del juego)
    sf::View originalView = window.getView();

    // Establece una vista est�tica para el men� de pausa
    sf::View pauseView = window.getDefaultView(); // O define una vista fija
    window.setView(pauseView); // Cambia la vista a la est�tica


    if (_seleccion == 0) {
        // Dibuja la opci�n "Continuar"
        window.draw(_continuarSprite);
    }
    else if (_seleccion == 1) {
        // Dibuja la opci�n "Salir"
        window.draw(_salirSprite);
    }
}

bool Pausa::getPausa(){return _pausa;}
void Pausa::open(){ _seleccion = 0;
     _pausa = true;
     _selectedOpc = -1;}
void Pausa::close(){_pausa = false;}
int Pausa::getSelecOpc(){return _selectedOpc;}
