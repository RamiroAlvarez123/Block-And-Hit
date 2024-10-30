#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <vector>


class Juego : public sf:Drawable {
protected:
    sf::color *colors;
    bool Tablero;
    sf::Text texto;
    sf::Texture imagen;
    sf::Sprite mostrarImagen;
    int Puntaje;
    std::vector<std::vector<piece>> piece;  /// vector de terminarjuego
public:
    Juego(int X, int Y, sf::Font &font, sf::Texture &imagen); ///contructor
    void setPuntaje(int Puntaje);
    int getPuntaje();
    int actualizarPuntos();
    void procesarEntrada(std::pair<int,int> dir);  /// ingreso y movimiento en X e Y
    void setPos(sf::Vector2f); /// vector 2D contiene X e Y
    sf::Vector2f getPos();
    bool terminarjuego();
    bool Ganaste();
    virtual void draw(sf::RenderTarget &rt,sf::RenderStates rs);

};









