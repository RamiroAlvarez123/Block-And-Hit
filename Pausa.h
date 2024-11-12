#pragma once
#include <SFML/Graphics.hpp>

class Pausa
{
    sf::RenderWindow* window;
    //sf::RenderWindow& window;

    sf::Texture _continuarTexture;
    sf::Sprite _continuarSprite;

    sf::Texture _salirTexture;
    sf::Sprite _salirSprite;


    sf::Event event;

    int _seleccion = 0;
    bool _pausa = false;
    int _selectedOpc = -1;
public:
    Pausa();

    // M�todos para dibujar el texto en la ventana
    void render(sf::RenderWindow& window);
    void update(sf::Event event);
    void open();
    void close();
    bool getPausa();
    int getSelecOpc();
};

