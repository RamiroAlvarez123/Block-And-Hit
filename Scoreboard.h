#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ScoreboardFile.h"


class Scoreboard {

private:
    sf::SoundBuffer _Buffer;
    sf::Sound sound;

    sf::Texture _topTexture;
    sf::Sprite _topSprite;

    //ArchiRank _ArchiRanking;

    int _SelectOpc = -1;

    bool _inScoreboard = false;

public:
    Scoreboard();

    void update(sf::Event event);

	void render(sf::RenderWindow& window);

	bool getScoreboard() const;

	void open();

	void close();

	int getSelectOpc() const;

};




























