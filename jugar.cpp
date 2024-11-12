#pragma once
#include "Jugar.h"

Jugar::Jugar(b2World& world) : _world(world)
{
	if (!_musicMenu.openFromFile("assets/sounds/levelMusic.wav"))
		return; // error

	_musicMenu.setVolume(25.0f);
	_musicMenu.setLoop(true);
}

void Jugar::update()
{
	_juego->update();
}

void Jugar::update(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			_pause = true;
		}
	}
}

void Jugar::render(sf::RenderWindow& window)
{
	_juego->render(window);
}

bool Jugar::getJugar() const
{
	return _jugar;
}

bool Jugar::getReintentar()
{
	return _juego->getReintentar();
}

bool Jugar::getPause() const
{
	return _pause;
}

void Jugar::crearJuego()
{
	_juego = new Juego(_world);
}

void Jugar::nuevoJuego() {
	if (_juego != nullptr) {
		delete _juego;
	}
	crearJuego();
}

void Jugar::reintentar() {
	_juego->reintentar();
}

void Jugar::open()
{
	_musicMenu.play();
	_pause = false;
	_jugar = true;
}

void Jugar::close()
{
	_jugar = false;
	_musicMenu.stop();
}
