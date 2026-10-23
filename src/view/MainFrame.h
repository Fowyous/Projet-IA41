#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include "Button.h"

class MainFrame
{
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    Button startButton;
    Button settingsButton;
    sf::Vector2f lastMousePos;
    bool isMousePressed;

    void updateLayout();

public:
    MainFrame();
    ~MainFrame() {}
    void run();
};

#endif