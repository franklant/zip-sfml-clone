#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "collidable.h"
#include "asteroid.h"
#include <vector>

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Collidable
{
public:
    // we need to set the player's x and y
    Player(float x, float y);

    void update(sf::RenderWindow &gameWindow, float deltaTime);
    void setSpeed(float newSpeed);

    std::vector<Bullet> getBulletList();
private:
    // vector of bullets
    std::vector<Bullet> _bullets;

    float _speed = 150;

    float _shootCooldown = 0.2f;
    float _shootTimer = 0;
    bool _canShoot = true;

    // the current "auto_increment" counter for bullet id's
    int _bulletIdCount = -1;

};

#endif