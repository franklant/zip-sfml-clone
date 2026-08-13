#include <SFML/Graphics.hpp>
#include "collidable.h"

#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid : public Collidable
{
public:
    Asteroid(float x, float y);

    void update(sf::RenderWindow &gameWindow, float deltaTime);
    
    bool readyToDelete() { return _canDelete; }
    void destroy() { _canDelete = true; }
private:
    float _speed = 150.0f;
    float _canDelete = false;
};

#endif