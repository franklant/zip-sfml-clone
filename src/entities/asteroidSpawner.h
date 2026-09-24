#include <SFML/Graphics.hpp>
#include "collidable.h"
#include "asteroid.h"
#include <vector>

#ifndef ASTEROIDSPAWNER_H
#define ASTEROIDSPAWNER_H

class AsteroidSpawner
{
public:
    AsteroidSpawner() = default;

    void update(sf::RenderWindow &gameWindow, bool isPaused, float deltaTime);

    std::vector<Asteroid> getAsteroidList();

private:
    std::vector<Asteroid> _asteroids;
};

#endif