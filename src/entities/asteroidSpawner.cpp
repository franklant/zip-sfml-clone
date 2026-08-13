#include "asteroidSpawner.h"
#include "../constants.h"

void AsteroidSpawner::update(sf::RenderWindow &gameWindow, float deltaTime)
{
    for (int i = 0; i < _asteroids.size(); i++)
    {
        _asteroids[i].update(gameWindow, deltaTime);
    }
}

std::vector<Asteroid> AsteroidSpawner::getAsteroidList()
{
    return _asteroids;
}