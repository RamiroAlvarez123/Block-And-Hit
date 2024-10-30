#ifndef LOGIN_H
#define LOGIN_H

#include <SFML/Graphics.hpp>
#include <string>


class Login {
public:
    Login();
    int Ingresar();
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    std::string inputText;
};

#endif
