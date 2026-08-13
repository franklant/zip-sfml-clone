#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "constants.h"
#include "button/button.h"


/// @brief Modifes the position of the shape using reference. Instead of assigning a variable
/// to the new return value reflecting the change, we can modify the original variable by
/// reference.
/// @param r The rectangle we want to move.
/// @param spd The speed at which we want to move the rectangle.
void moveShapeByRef(sf::RectangleShape &r, float spd, float deltaTime)
{
	// move to the left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		r.setPosition(sf::Vector2f(
			r.getPosition().x - spd * deltaTime,
			r.getPosition().y - 0
		));
	}

	// move to the right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		r.setPosition(sf::Vector2f(
			r.getPosition().x + spd * deltaTime,
			r.getPosition().y - 0
		));
	}

	// move up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		r.setPosition(sf::Vector2f(
			r.getPosition().x - 0,
			r.getPosition().y - spd * deltaTime
		));
	}

	// move down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		r.setPosition(sf::Vector2f(
			r.getPosition().x - 0,
			r.getPosition().y + spd * deltaTime
		));
	}
}

void keepInBoundsByRef(sf::RectangleShape &r)
{
	// if crossing the right border
	if (r.getPosition().x >= Constants::WINDOW_WIDTH)
	{
		r.setPosition(sf::Vector2f(
			0 - r.getSize().x,
			r.getPosition().y
		));
	}

	// if crossing the left border
	if (r.getPosition().x + r.getSize().x <= -0.5)
	{
		r.setPosition(sf::Vector2f(
			Constants::WINDOW_WIDTH,
			r.getPosition().y
		));
	}

	// if crossing the bottom border
	if (r.getPosition().y >= Constants::WINDOW_HEIGHT)
	{
		r.setPosition(sf::Vector2f(
			r.getPosition().x,
			0 - r.getSize().y
		));
	}

	// if crossing the top border
	if (r.getPosition().y + r.getSize().y <= -0.5)
	{
		r.setPosition(sf::Vector2f(
			r.getPosition().x,
			Constants::WINDOW_HEIGHT
		));
	}
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
	
	// create the rectangle
	sf::Vector2f rectSize(20.0f, 20.0f);
	sf::RectangleShape rect(rectSize);

	// set the color and position of rectangle
	rect.setFillColor(sf::Color::Blue);
	rect.setPosition(sf::Vector2f(
		(Constants::WINDOW_WIDTH / 2.0f) - (rectSize.x / 2.0f),
		(Constants::WINDOW_HEIGHT / 2.0f) - (rectSize.y / 2.0f)
	));

	// create button
	Button button(10.0f, 20.0f);
	std::cout << "Button pressed? " << button.isPressed() << std::endl;

	
	float speed = 100.0f;
	sf::Clock clock;
	
	//
	//
	//
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

		// std::cout << "Delta time: " << deltaTime.asSeconds() << std::endl;

		moveShapeByRef(rect, speed, deltaTime.asSeconds());
		keepInBoundsByRef(rect);

		button.update(window, deltaTime.asSeconds());

		window.draw( rect );
		window.draw( button );
		window.display();
	}
}
