#include <SFML/Graphics.hpp>
#include "collidable.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet : public Collidable
{
public:
    // we need to set the player's x and y
    Bullet(float x, float y);

    void update(sf::RenderWindow &gameWindow, float deltaTime);

    void setId(int id);
    int  getId();
private:
    void setCenter();
    
    // sf::RectangleShape _hitBox;

    float _speed = 300;

    float _bulletId = -1;
};

#endif