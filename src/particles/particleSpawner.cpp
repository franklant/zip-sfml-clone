#include "particleSpawner.h"
#include "../constants.h"
#include <random>
#include <iostream>

void ParticleSpawner::spawnParticle()
{
    // genereate a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xAxisDistribution(0, Constants::WINDOW_WIDTH - 100.0f);

    // Generate random number in the range [min, max]
    int randomXCoord = xAxisDistribution(gen);
    
    // spawn the asteroid at the random x position
    Particle *spawnedParticle = new Particle(randomXCoord, -100.0f / 2);
    
    _particles.push_back(*spawnedParticle);

    delete spawnedParticle;
}

void ParticleSpawner::update(sf::RenderWindow &gameWindow, bool isPaused, float deltaTime)
{
    if (!isPaused)
    {
        // draw and update the particle
        for (int i = _particles.size() - 1; i >= 0; i--)
        {
            gameWindow.draw(_particles[i]);
            _particles[i].update(gameWindow, isPaused, deltaTime);

            // if the bullet leaves the screen, delete it   
            if (_particles[i].getPosition().y >= Constants::WINDOW_HEIGHT || _particles[i].readyToDelete())
            {
                // erase the object and free it's memory
                _particles.erase(_particles.begin() + i);
            }
        }

        // asteroid spawn timer
        if (_particleSpawnTime >= _particleSpawnCooldown)
        {
            spawnParticle();
            _particleSpawnTime = 0;
        } else {
            _particleSpawnTime += deltaTime;
        }
    }
}

std::vector<Particle> ParticleSpawner::getParticleList()
{
    return _particles;
}