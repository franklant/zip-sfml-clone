#include <SFML/Graphics.hpp>
#include <vector>

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

// every object that performs collision will call inherit this class
class Collidable : public sf::RectangleShape 
{
public:
    // we need to set the player's x and y
    Collidable() = default;

    // what we'll use to check for collision
    bool checkCollision(Collidable &other);

protected:
    sf::Vector2f _position;
    sf::Vector2f _size;
};

#endif