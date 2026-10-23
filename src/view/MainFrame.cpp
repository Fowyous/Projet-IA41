#include "MainFrame.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void MainFrame::updateLayout()
{
    sf::Vector2f windowSize(window.getSize());

    float padding = 20.f;
    float buttonWidth = (windowSize.x * 0.5f) / 2;
    float buttonHeight = windowSize.y * 0.1f;

    // Center title horizontally
    sf::FloatRect titleBounds = title.getLocalBounds();
    float titleX = (windowSize.x - titleBounds.size.x) / 2;
    title.setPosition(sf::Vector2f(titleX, padding));

    // Calculate total width of both buttons with padding between them
    float totalButtonsWidth = buttonWidth * 2 + padding;

    // Center buttons horizontally and vertically
    float startX = (windowSize.x - totalButtonsWidth) / 2;
    float startY = (windowSize.y - buttonHeight) / 2;

    // Start button - left
    startButton.setPosition(sf::Vector2f(startX, startY));
    startButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));

    // Settings button - right
    settingsButton.setPosition(sf::Vector2f(startX + buttonWidth + padding, startY));
    settingsButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
}

void MainFrame::run()
{
    while (window.isOpen())
    {
        while (window.isOpen())
        {
            while (auto event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
                else if (event->is<sf::Event::Resized>())
                {
                    updateLayout();
                }
                else if (event->is<sf::Event::MouseMoved>())
                {
                    lastMousePos = window.mapPixelToCoords(event->getIf<sf::Event::MouseMoved>()->position);
                }
                else if (event->is<sf::Event::MouseButtonPressed>())
                {
                    isMousePressed = true;
                }
                else if (event->is<sf::Event::MouseButtonReleased>())
                {
                    isMousePressed = false;
                }
            }
            // Update button states
            startButton.update(lastMousePos, isMousePressed);
            settingsButton.update(lastMousePos, isMousePressed);
            // Clear and draw
            window.clear(sf::Color(30, 30, 30));
            window.draw(title);
            startButton.draw(window);
            settingsButton.draw(window);
            window.display();
        }
    }
}

MainFrame::MainFrame() : window(sf::VideoMode({700, 400}), "SFML Application"),
                         font("AdwaitaMono-BoldItalic.ttf"),
                         title(font, "Rasender Roboter", 90),
                         startButton(font, "Start", 0, 0, 150, 60),
                         settingsButton(font, "Settings", 0, 0, 150, 60),
                         lastMousePos(0, 0),
                         isMousePressed(false)
{
    window.setFramerateLimit(60);

    title.setFillColor(sf::Color::White);

    startButton.setColors(sf::Color(70, 130, 180), sf::Color(100, 160, 220), sf::Color(255, 100, 100));
    settingsButton.setColors(sf::Color(70, 130, 180), sf::Color(100, 160, 220), sf::Color(255, 100, 100));

    updateLayout();
}