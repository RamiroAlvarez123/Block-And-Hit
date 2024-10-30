#include "Login.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Login::Login()
{

}


int Login::Ingresar() {

sf::Texture backgroundTexture;
sf::Sprite background;
sf::Font font;
sf::Text text;

text.setFont(font);
text.setCharacterSize(60);
sf::Color customColor(119, 110, 101, 255);
text.setFillColor(customColor);
text.setPosition(50, 100);
text.setLetterSpacing(26);

    if(!backgroundTexture.loadFromFile("imgs/login 2.png")){
        std::cout<<"Error al cargar la textura\n";
    }

    if (!font.loadFromFile("fuente.ttf")) {
        return -1;
    }

    std::string inputText = "";

   background.setTexture(backgroundTexture);
   background.setPosition(0,0);

    sf::RenderWindow window(sf::VideoMode(491,241), "login", sf::Style::Titlebar | sf::Style::Close);
   window.setFramerateLimit(60);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed) window.close();


            if (event.type == sf::Event::TextEntered) {
                // Ignorar la tecla de "retroceso" o si el carácter no es imprimible
                if (event.text.unicode == '\b') {
                    if (!inputText.empty()) {
                        inputText.pop_back();  // Eliminar último carácter
                    }
                }
                else if (event.text.unicode < 128) {  // Solo caracteres ASCII

                        if(inputText.length() < 5){
                    inputText += static_cast<char>(event.text.unicode);  // Añadir el carácter al texto
                        }
                }
                if(event.text.unicode == '\n') {
                                            ///SEGUIR ACA
                }
            }
        }

     text.setString(inputText);
    std::cout<<inputText;
    window.clear();
    window.draw(background);
    window.draw(text);
    window.display();
   }

   return 0;
}
