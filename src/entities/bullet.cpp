#include <iostream>
#include "bullet.h"

Bullet::Bullet(float x, float y)
{
    _position = sf::Vector2f(x, y);
    _size = sf::Vector2f(15.0f, 15.0f);

    setPosition(_position);
    setSize(_size);
    setFillColor(sf::Color::Yellow);
}

void Bullet::update(sf::RenderWindow &gameWindow, float deltaTime)
{
    // don't run update loop if the bullet's id has not been set
    if (_bulletId == -1) 
    {
        std::cout << "[ERROR] bullet's id has not been set;" << std::endl;
        return;
    }

    // have it go move up indefinitely
    _position.y -= _speed * deltaTime;

    setPosition(_position);
}

void Bullet::setId(int id)
{
    _bulletId = id;
}

int Bullet::getId()
{
    return _bulletId;
}

void Bullet::setCenter()
{
    // set the origin to be the center of the object, not top left corner
    setOrigin(sf::Vector2f(
        _size.x / 2.0f,
        _size.y / 2.0f
    ));
}