#include <SFML/Graphics.hpp>

#ifndef BUTTON_H
#define BUTTON_H

class Button : public sf::RectangleShape {
public:
    Button(float x = 0, float y = 0, sf::Vector2f buttonSize = sf::Vector2f(300.0f, 100.0f));

    void update(sf::Window &gameWindow, float deltaTime);
    bool isPressed();
    bool isHovered();

private:

    void changeColors();
    
    bool _isHovered = false;
    bool _isPressed = false;

    sf::Color _defaultColor = sf::Color::Green;
    sf::Color _hoverColor = sf::Color::Yellow;
    sf::Color _clickedColor = sf::Color::Blue;

    sf::Vector2f _position = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f _size = sf::Vector2f(0.0f, 0.0f);
};

#endif