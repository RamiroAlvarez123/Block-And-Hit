#pragma once
#include <iostream>
#include "Juego.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Win {

private:

    Juego* _juego;

    float _tiempo = 10.0f;
    float _tiempoRestante;
    sf::Clock _clock;
    sf::Text _timerText;

    sf::Texture _winTexture;
    sf::Sprite _winSprite;
    sf::Font _font;
    bool _win = false;
public:

    Win();

    void update();
    void render(sf::RenderWindow& window);
    bool getWin();
    void open();
    void close();



};
