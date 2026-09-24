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

    void update(sf::RenderWindow &gameWindow, bool isPaused, float deltaTime);
    void setSpeed(float newSpeed);

    void destroyBulletAt(int index);

    void decrementHealthBy(int decrementValue) { _health -= decrementValue; }
    
    void setHealth(int healthValue) { _health = healthValue; }
    int getHealth() { return _health; }

    void spaceReleased(bool released) { _spaceReleased = released; }
    

    std::vector<Bullet> getBulletList();
private:
    // vector of bullets
    std::vector<Bullet> _bullets;

    float _speed = 250;

    float _shootCooldown = 0.6f;
    float _shootTimer = 0;
    bool _canShoot = true;

    bool _spaceWasPressed = false;
    bool _spaceReleased = false;

    // the current "auto_increment" counter for bullet id's
    int _bulletIdCount = -1;
    int _health = 0;

};

#endif