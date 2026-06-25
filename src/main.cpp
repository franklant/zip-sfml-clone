#include <SFML/Graphics.hpp>
#include "constants.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( { Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT } ), "SFML works!" );
	sf::CircleShape shape( 100.f );
	shape.setFillColor( sf::Color::Green );

	// EVENT LOOP : while the window is open
	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		window.draw( shape );
		window.display();
	}
}
