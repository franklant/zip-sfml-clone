#include <SFML/Graphics.hpp>
#include <vector>

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle : public sf::RectangleShape
{
public:
    // we need to set the player's x and y
    Particle(float x, float y);

    void update(sf::RenderWindow &gameWindow, bool isPaused, float deltaTime);
    void setSpeed(float newSpeed);

    bool readyToDelete() { return _canDelete; }
    void destroy() { _canDelete = true; }

protected:
    sf::Vector2f _position;
    sf::Vector2f _size;

    float _speed = 350;

    int _health = 0;

    bool _canDelete = false;
};

#endif