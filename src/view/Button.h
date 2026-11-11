#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button
{
private:
    sf::RectangleShape rect;

    bool isHovered;
    bool isPressed;
    std::function<void()> toExecuteOnPressed;//a method to be executed 
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    sf::Text text;

public:
    Button(const sf::Font &font, const std::string &label,
           float x, float y, float width, float height, std::function<void()> toExecuteOnPressed);

    void setColors(const sf::Color &normal, const sf::Color &hover, const sf::Color &pressed);
    void update(const sf::Vector2f &mousePos, bool mousePressed);
    void draw(sf::RenderWindow &window);

    void setPosition(const sf::Vector2f &position);
    void setSize(const sf::Vector2f &size);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
};

#endif
