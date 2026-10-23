#include "Button.h"

Button::Button(const sf::Font& font, const std::string& label,
               float x, float y, float width, float height)
    : isHovered(false), isPressed(false),
      normalColor(100, 100, 100),
      hoverColor(150, 150, 150),
      pressedColor(200, 50, 50),
      text(font, label, 20)
{
    // Setup rectangle
    rect.setSize(sf::Vector2f(width, height));
    rect.setPosition(sf::Vector2f(x, y));
    rect.setFillColor(normalColor);
    
    // Setup text
    text.setFillColor(sf::Color::White);
    
    // Center text within button
    sf::FloatRect textBounds = text.getLocalBounds();
    float textX = x + (width - textBounds.size.x) / 2;
    float textY = y + (height - textBounds.size.y) / 2 - 5;
    text.setPosition(sf::Vector2f(textX, textY));
}

void Button::setColors(const sf::Color& normal, const sf::Color& hover, const sf::Color& pressed)
{
    normalColor = normal;
    hoverColor = hover;
    pressedColor = pressed;
}

void Button::update(const sf::Vector2f& mousePos, bool mousePressed)
{
    sf::FloatRect buttonBounds = rect.getGlobalBounds();
    isHovered = buttonBounds.contains(mousePos);
    
    if (isHovered && mousePressed)
    {
        isPressed = true;
        rect.setFillColor(pressedColor);
    }
    else if (isHovered)
    {
        isPressed = false;
        rect.setFillColor(hoverColor);
    }
    else
    {
        isPressed = false;
        rect.setFillColor(normalColor);
    }
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(rect);
    window.draw(text);
}

void Button::setPosition(const sf::Vector2f& position)
{
    float offsetX = position.x - rect.getPosition().x;
    float offsetY = position.y - rect.getPosition().y;
    
    rect.setPosition(position);
    text.setPosition(sf::Vector2f(text.getPosition().x + offsetX, text.getPosition().y + offsetY));
}

void Button::setSize(const sf::Vector2f& size)
{
    rect.setSize(size);
    
    // Recenter text
    sf::FloatRect textBounds = text.getLocalBounds();
    float textX = rect.getPosition().x + (size.x - textBounds.size.x) / 2;
    float textY = rect.getPosition().y + (size.y - textBounds.size.y) / 2 - 5;
    text.setPosition(sf::Vector2f(textX, textY));
}

sf::Vector2f Button::getPosition() const
{
    return rect.getPosition();
}

sf::Vector2f Button::getSize() const
{
    return rect.getSize();
}
