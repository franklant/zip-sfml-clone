#include <iostream>
#include "..\constants.h"
#include "player.h"
#include "bullet.h"

Player::Player(float x, float y)
{

    // Set the position so that the ship sits right above the bottom border
    _size = sf::Vector2f(30.0f, 40.0f);
    _position = sf::Vector2f(
        (Constants::WINDOW_WIDTH / 2.0f) - _size.x, 
        Constants::WINDOW_HEIGHT - _size.y
    );

    setPosition(_position);                 // set the initial position
    setSize(_size);
    setFillColor(sf::Color::Green);

    setHealth(3);
}

void Player::update(sf::RenderWindow &gameWindow, bool isPaused, float deltaTime)
{
    // only update when the game isn't paused.
    if (!isPaused) 
    {
        // move ship to the left if it's not on the left border
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && _position.x > 0)
        {
            _position.x -= _speed * deltaTime;
        }

        // move ship to the right if it's not on the right border
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && _position.x + _size.x < Constants::WINDOW_WIDTH)
        {
            _position.x += _speed * deltaTime;
        }

        // Shoot bullet
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) _spaceWasPressed = true;
        if (_spaceReleased && _canShoot)
        //if (_spaceWasPressed && _spaceReleased && _canShoot)
        {
            // spawn bullet at center
            // 15px is the size of the bullet (hardcoded ofc)
            Bullet bullet(
                _position.x + (getSize().x / 2.0f) - (15.0f / 2.0f),
                _position.y + (getSize().y / 2.0f) - (15.0f / 2.0f)
            );

            // set the id of the bullet
            _bulletIdCount++;
            bullet.setId(_bulletIdCount);

            _bullets.push_back(bullet);

            _canShoot = false;
            _spaceReleased = false;
            _spaceWasPressed = false;
        }

        // shoot timer
        if (!_canShoot) 
        {
            _shootTimer += deltaTime;

            if (_shootTimer >= _shootCooldown)
            {
                _canShoot = true;
                _shootTimer = 0;
            }
        }

        // update bullets and check if it's still on screen
        for (int i = _bullets.size() - 1; i >= 0; i--)
        {
            _bullets[i].update(gameWindow, isPaused, deltaTime);

            // if the bullet leaves the screen, delete it   
            if (_bullets[i].getPosition().y <= 0 || _bullets[i].readyToDelete())
            {
                // erase the object and free it's memory
                _bullets.erase(_bullets.begin() + i);
            }
        }

        // reset the bullet id counter if it reaches max int or if the bullet vector is empty
        if (_bulletIdCount >= INT_MAX || _bullets.empty()) 
        {
            _bulletIdCount = -1;
        }

        setPosition(_position);
    }
}

void Player::setSpeed(float newSpeed)
{
    _speed = newSpeed;
}

std::vector<Bullet> Player::getBulletList()
{
    return _bullets;
}

void Player::destroyBulletAt(int index)
{
    // erase the object and free it's memory
    _bullets[index].destroy();
}