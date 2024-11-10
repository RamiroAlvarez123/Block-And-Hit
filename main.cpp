#include "SceneManager.h"
#include <box2d/box2d.h>

int main(){

   sf::RenderWindow window(sf::VideoMode(800,480), "Block And Hit");
    window.setFramerateLimit(60);

    std::unique_ptr<b2World> world;
	b2Vec2 gravity(0.0f, 980.0f);
	world = std::make_unique<b2World>(gravity);
	world->SetContactListener(new GlobalContactListener());

    SceneManager SceneManager(*world);
   while(window.isOpen())
   {

    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed)
            {
                window.close();
            }

        else{
        SceneManager.update(event);
     }
    }

        SceneManager.update();

    window.clear();
    SceneManager.render(window);
    window.display();
   }

   return 0;
}
