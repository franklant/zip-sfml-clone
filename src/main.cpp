#include <SFML/Graphics.hpp>
#include "entities/player.h"
#include "entities/asteroid.h"
#include "entities/bullet.h"
#include "entities/asteroid.h"
#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

/// @brief This method is called once at the beginning of runtime (Only serves an organizational purpose).
void start() 
{
    // code here ...
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

    start();

    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;

    asteroids.push_back(test);

    float asteroidSpawnTime = 0;
    float asteroidSpawnCooldown = 2;

    sf::Clock clock;
	
	// EVENT LOOP : while the window is open
	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();

		// Using sf::Clock.restart() to return the elapsed time since the last frame (delta time)
		sf::Time deltaTime = clock.restart();
        
        // update the bullet list
        bullets = p1.getBulletList();

        // draw bullet and check collision
        for (Bullet &bullet : bullets)
        {
            window.draw(bullet);

            // collision testing
            for (Asteroid &asteroid : asteroids)
            {
                if (bullet.checkCollision(asteroid))
                {
                    asteroid.destroy();
                }
            }
        }

        // draw asteroids
        for (int i = 0; i < asteroids.size(); i++)
        {
            asteroids[i].update(window, deltaTime.asSeconds());
            window.draw(asteroids[i]);

            // if an asteroid is marked for deletion then delete
            if (asteroids[i].readyToDelete())
            {
                // erase the object and free it's memory
                asteroids.erase(asteroids.begin() + i);
                asteroids.shrink_to_fit();
            }
        }

        // asteroid spawn timer
        if (asteroidSpawnTime >= asteroidSpawnCooldown)
        {
            std::cout << "Spawn Asteroid" << std::endl;
            asteroidSpawnTime = 0;
        } else {
            asteroidSpawnTime += deltaTime.asSeconds();
        }

        p1.update(window, deltaTime.asSeconds());

        window.draw(p1);

		window.display();
	}

    return 0;
}