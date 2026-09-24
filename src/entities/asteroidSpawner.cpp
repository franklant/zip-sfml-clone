#include "asteroidSpawner.h"
#include "../constants.h"

void AsteroidSpawner::update(sf::RenderWindow &gameWindow, bool isPaused, float deltaTime)
{
    if (!isPaused)
    {
        for (int i = 0; i < _asteroids.size(); i++)
        {
            _asteroids[i].update(gameWindow, isPaused, deltaTime);
        }
    }
}

std::vector<Asteroid> AsteroidSpawner::getAsteroidList()
{
    return _asteroids;
}