
#include "Login.h"
#include <iostream>
#include <SFML/Graphics.hpp>

sf::Texture backgroundTexture;
sf::Sprite background;

int main(){


    Login ingresarUsuario;
    ingresarUsuario.Ingresar();

    // carga la imagen con el path dado
    if(!backgroundTexture.loadFromFile("imgs/interfaz.png")){
        std::cout<<"Error al cargar la textura\n";
    }

    // asigna la imagen al objeto background y lo posiciona en las coordenadas (0, 0)
   background.setTexture(backgroundTexture);
   background.setPosition(0,0);

    // crea una ventana de tamaño 530x606, de titulo "2048" y que no permite la modificacion del tamaño
   sf::RenderWindow window(sf::VideoMode(530,606), "2048", sf::Style::Titlebar | sf::Style::Close);
   window.setFramerateLimit(60);

   //bucle que se ejecuta mientras la ventana este abierta
   while(window.isOpen()){

    //procesa los posibles eventos de la ventana
    sf::Event event;
    while(window.pollEvent(event)){
        //cierra la ventana y el programa
        if(event.type==sf::Event::Closed) window.close();
    }

    //limpia la ventana
    window.clear();
   //dibuja la imagen en la ventana
    window.draw(background);
    //muestra el contenido
    window.display();
   }

   return 0;
}
