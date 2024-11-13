#include "SceneManager.h"

SceneManager::SceneManager(b2World& world) {
	_scene = new Scene(world);
}

void SceneManager::update() {
	_scene->update();
}

void SceneManager::update(sf::Event event) {
	_scene->update(event);
}

void SceneManager::render(sf::RenderWindow& window) {
	_scene->render(window);
}

bool SceneManager::salir() const{
    return _scene->salir();
}
