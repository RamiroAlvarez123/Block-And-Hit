#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Reintentar
{
private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;

    sf::Texture _yesTexture;
    sf::Sprite _yesSprite;

    sf::Texture _noTexture;
    sf::Sprite _noSprite;

    int _reintentarSelection = 0;
    int _selectedOption = -1;

    bool _reintentar = false;
public:
    Reintentar();

	void update(sf::Event event);

	void render(sf::RenderWindow& window);

	int getSelectedOption() const;

    bool getReintentar() const;

	void open();

	void close();
};

