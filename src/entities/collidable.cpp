#include "collidable.h"

bool Collidable::checkCollision(Collidable &other)
{
    if (
        _position.x <= other._position.x + other._size.x &&
        _position.x + _size.x >= other._position.x &&
        _position.y <= other._position.y + other._size.y &&
        _position.y + _size.y >= other._position.y
    ) {
        return true;
    }

    return false;
}