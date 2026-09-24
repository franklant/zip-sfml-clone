#include <SFML/Graphics.hpp>
#include "particle.h"
#include <vector>

#ifndef PARTICLESPAWNER_H
#define PARTICLESPAWNER_H

class ParticleSpawner
{
public:
    ParticleSpawner() = default;

    void update(sf::RenderWindow &gameWindow, bool isPaused, float deltaTime);

    std::vector<Particle> getParticleList();

private:
    void spawnParticle();

    std::vector<Particle> _particles;

    float _particleSpawnTime = 0;
    float _particleSpawnCooldown = 0.05;
};

#endif