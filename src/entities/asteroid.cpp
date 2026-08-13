#include "asteroid.h"
#include "../constants.h"
#include <iostream>

Asteroid::Asteroid(float x, float y)
{
    // Set the position so that the ship sits right above the bottom border
    _size = sf::Vector2f(100.0f, 100.0f);
    _position = sf::Vector2f(x, y);

    setPosition(_position);                 // set the initial position
    setSize(_size);
    setFillColor(sf::Color::Red);
}

void Asteroid::update(sf::RenderWindow &gameWindow, float deltaTime)
{
    _position.y += _speed * deltaTime;

    setPosition(_position);
}