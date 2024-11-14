#pragma once
#include <iostream>
#include "Juego.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Win {

private:

    sf::Texture _winTexture;
    sf::Sprite _winSprite;

    sf::SoundBuffer _buffer;
	sf::Sound _sound;

    sf::Font _font;

    int _selected = -1;
    bool _win = false;
public:

    Win();

    void update(sf::Event event);
    void render(sf::RenderWindow& window);
    bool getWin();
    void open();
    void close();
    int getSelected();



};
