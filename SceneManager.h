#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Scene.h"
#include "Menu.h"
class SceneManager {
private:
    Scene* _scene;
public:
    SceneManager(b2World& world);

    void update();

    void update(sf::Event event);

    void render(sf::RenderWindow& window);

    bool salir() const;
};
