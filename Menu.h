#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu{

private:
sf::Texture _jugarTexture;
sf::Sprite _jugarSprite;

sf::Texture _rankTexture;
sf::Sprite _rankSprite;

sf::Texture _salirTexture;
sf::Sprite _salirSprite;

sf::SoundBuffer _Buffer;
sf::Sound _sound;
sf::Music Musicmenu;

bool _menuOpc;
int _menuSelecOpc;
int _inMenu = true;

public:

Menu();
void update(sf::Event event);
void render(sf::RenderWindow& window);
bool getMenu() const;
bool getSalida() const;
void open(bool music = false);
void close(bool music = false);
int getSelectedOpc() const;
};
