#include "particle.h"


Particle::Particle(float x, float y)
{
    // Set the position so that the ship sits right above the bottom border
    _size = sf::Vector2f(5.0f, 5.0f);
    _position = sf::Vector2f(x, y);

    setPosition(_position);                 // set the initial position
    setSize(_size);
    setFillColor(sf::Color::White);
}

void Particle::update(sf::RenderWindow &gameWindow, bool isPaused, float deltaTime)
{
    if (!isPaused) 
    {
        _position.y += _speed * deltaTime;

        setPosition(_position);
    }
}