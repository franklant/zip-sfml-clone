
#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"

Button::Button(float x, float y, sf::Vector2f buttonSize) 
{
    // create the shape and set the position of the rectangle
    setPosition(sf::Vector2f(x, y));
    setSize(buttonSize);
    setFillColor(_defaultColor);

    _position = getPosition();
    _size = getSize();
}

void Button::changeColors() 
{
    if (_isHovered) {
        setFillColor(_hoverColor);
    }

    else if (_isPressed) {
        setFillColor(_clickedColor);
    }

    else {
        setFillColor(_defaultColor);
    }
}

void Button::update(sf::Window &gameWindow, float deltaTime)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(gameWindow);
    // std::cout << "Tracking Mouse Coords: { " << mousePosition.x << ", " << mousePosition.y << " }" << std::endl;

    // check if the mouse is inside of the button
    if (
        mousePosition.x <= _position.x + _size.x &&
        mousePosition.x >= _position.x &&
        mousePosition.y <= _position.y + _size.y &&
        mousePosition.y >= _position.y && !_isPressed
    )
    {
        _isHovered = true;
    } 
    else 
    {
        _isHovered = false;
    }

    // check if the button is clicked
    if (_isHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        _isPressed = true;
    }

    if (_isPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        _isPressed = false;
    }

    changeColors();
}

bool Button::isHovered()
{
    return _isHovered;
}

bool Button::isPressed()
{
    return _isPressed;
}