#include <SFML/Graphics.hpp>
#include "entities/player.h"
#include "entities/asteroid.h"
#include "entities/bullet.h"
#include "entities/asteroid.h"
#include "particles/particleSpawner.h"
#include "constants.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>

// TODO: ASTEROIDS ARE NOT DELETING CORRECTLY (it was really the collision code)


/// @brief This method is called once at the beginning of runtime (Only serves an organizational purpose).
void start() 
{
    // code here ...
}

void spawnAsteroid(std::vector<Asteroid> &asteroidList)
{
    // genereate a random number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xAxisDistribution(0, Constants::WINDOW_WIDTH - 100.0f);

    // Generate random number in the range [min, max]
    int randomXCoord = xAxisDistribution(gen);
    
    // spawn the asteroid at the random x position
    Asteroid *spawnedAsteroid = new Asteroid(randomXCoord, -110.0f / 2);
    
    asteroidList.push_back(*spawnedAsteroid);

    delete spawnedAsteroid;
}

int main() 
{
    // configure window
	std::string title = "SFML Zip Clone";
	sf::RenderWindow window(
		sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}),
		title,
		sf::Style::Default,
		sf::State::Windowed
	);

    Player p1(Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT - 25.0f);
    Asteroid test(50, 0);

    const sf::Font font("./assets/static/NotoSans_Condensed-Light.ttf");
    
    //// UI

    // draw the title
    sf::Text titleText(font, "THE GALAGA");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(sf::Vector2f(0, 0));

    // draw the health
    sf::Text healthText(font, "HEALTH: 3");
    healthText.setCharacterSize(30);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition(sf::Vector2f(Constants::WINDOW_WIDTH - 100, 0));

    // draw the score
    sf::Text scoreText(font, "0");
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f((Constants::WINDOW_WIDTH / 2) - 2.5f, 0));

    // draw game over text
    sf::Text gameOverText(font, "GAMEEEE OVER!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Yellow);
    gameOverText.setPosition(sf::Vector2f(Constants::WINDOW_WIDTH / 2.0f - 150, Constants::WINDOW_HEIGHT / 2.0f));
    

    // TODO: Display the health of the player

    start();

    ParticleSpawner particleSpawner;

    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;

    asteroids.push_back(test);

    float asteroidSpawnTime = 0;
    float asteroidSpawnCooldown = 2;

    int score = 0;

    bool isPaused = false;
    
    // debug
    bool spaceReleased = false;
    

    sf::Clock clock;
	
	// EVENT LOOP : while the window is open
	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
            
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                if (keyReleased->scancode == sf::Keyboard::Scan::Space)
                {
                    std::cout << "space released" << std::endl;
                    
                    // change the flag for the player to shoot on release
                    p1.spaceReleased(true);
                }
            }
		}

		window.clear();

		// Using sf::Clock.restart() to return the elapsed time since the last frame (delta time)
		sf::Time deltaTime = clock.restart();

        // check if the player's health is 0
        if (p1.getHealth() <= 0)
        {
            isPaused = true;
            window.draw(gameOverText);
        }
        
        // update the bullet list
        bullets = p1.getBulletList();

        // draw bullet and check collision
        for (int i = bullets.size() - 1; i >= 0; i--)
        {
            window.draw(bullets[i]);

            // collision testing
            for (int j = asteroids.size() - 1; j >= 0; j--)
            {
                if (bullets[i].checkCollision(asteroids[j]))
                {
                    score += 1;
                    asteroids[j].destroy();
                    p1.destroyBulletAt(i);
                }
            }
        }

        // spawn particles in the background
        particleSpawner.update(window, isPaused, deltaTime.asSeconds());

        // draw asteroids
        for (int i = asteroids.size() - 1; i >= 0; i--)
        {
            asteroids[i].update(window, isPaused, deltaTime.asSeconds());
            window.draw(asteroids[i]);

            // asteroid collision with player
            if (asteroids[i].checkCollision(p1))
            {
                asteroids[i].destroy();

                p1.decrementHealthBy(1);
            }

            // if an asteroid leaves the screen or is marked for deletion then delete
            if (asteroids[i].getPosition().y >= Constants::WINDOW_HEIGHT)
            {
                // also decrease the player's health
                // NOTE: could also try 0.5
                p1.decrementHealthBy(1);

                // erase the object and free it's memory
                asteroids.erase(asteroids.begin() + i);
            }

            // if an asteroid leaves the screen or is marked for deletion then delete
            if (asteroids[i].readyToDelete())
            {
                // erase the object and free it's memory
                asteroids.erase(asteroids.begin() + i);
            }

        }

        // asteroid spawn timer
        if (asteroidSpawnTime >= asteroidSpawnCooldown)
        {
            spawnAsteroid(asteroids);
            asteroidSpawnTime = 0;
        } else {
            asteroidSpawnTime += deltaTime.asSeconds();
        }

        p1.update(window, isPaused, deltaTime.asSeconds());

        healthText.setString("Health: " + std::to_string(p1.getHealth()));
        scoreText.setString(std::to_string(score));

        // std::cout << "Particle Count: " << particleSpawner.getParticleList().size() << std::endl;
        // std::cout << "Asteroid Count: " << asteroids.size() << std::endl;

    
        window.draw(titleText);
        window.draw(healthText);
        window.draw(scoreText);

        window.draw(p1);

		window.display();
	}

    return 0;
}