#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <algorithm>
#include <cstddef>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "GameFrame.h"
#include "GameConfig.h"

using namespace GameConfig;


GameFrame::GameFrame(sf::RenderWindow& window)
    : window(window),
      font(kFontPath),
      clockText(font, "00:00", 48)
{
    window.setFramerateLimit(60);
    clockText.setFillColor(sf::Color::White);

    setPlayers({"Alice", "Bob", "Charlie"});//test players to remove
    updateLayout();
}
void GameFrame::setPlayers(std::vector<std::string> names)
{
    if (names.size() < 2)
        throw std::invalid_argument("At least two players are required.");

    players = std::move(names);
    currentPlayer = 0;
    updateLayout();
}

void GameFrame::setCurrentPlayer(std::size_t index)
{
    if (index >= players.size())
        throw std::out_of_range("Invalid player index.");

    currentPlayer = index;
}

void GameFrame::setClock(const std::string& time)
{
    clockText.setString(time);
    centerClock();
}

void GameFrame::centerClock()
{
    clockText.setOrigin(clockText.getLocalBounds().getCenter());
    clockText.setPosition(clockArea.getCenter());
}

void GameFrame::updateLayout()
{
    const sf::Vector2f size(window.getSize());
    const float topH   = size.y * 0.10f;
    const float leftW  = size.x / 3.f;                   // left third
    const float splitY = topH + (size.y - topH) * 0.6f;  // player list / color box
    const float pad    = 15.f;

    clockArea  = sf::FloatRect(sf::Vector2f(0.f, 0.f),          sf::Vector2f(size.x, topH));
    boardRect  = sf::FloatRect(sf::Vector2f(leftW, topH),       sf::Vector2f(size.x - leftW, size.y - topH));
    playerPanel = sf::FloatRect(sf::Vector2f(0.f, topH),        sf::Vector2f(leftW, splitY - topH));
    colorPanel  = sf::FloatRect(sf::Vector2f(0.f, splitY),      sf::Vector2f(leftW, size.y - splitY));

    // Player rows
    const float titleH = 45.f;
    const float available = playerPanel.size.y - titleH - pad;
    const float rowH = std::min(55.f, available / static_cast<float>(players.size()));

    playerRows.clear();
    for (std::size_t i = 0; i < players.size(); ++i)
    {
        const float y = playerPanel.position.y + titleH + static_cast<float>(i) * rowH;
        playerRows.push_back(sf::FloatRect(
            sf::Vector2f(playerPanel.position.x + pad, y),
            sf::Vector2f(playerPanel.size.x - 2.f * pad, rowH - 6.f)));
    }

    // Color circles and their buttons
    const float colW = colorPanel.size.x / static_cast<float>(kColors.size());
    circleRadius = std::min(colW * 0.35f, colorPanel.size.y * 0.2f);
    const float cy = colorPanel.position.y + colorPanel.size.y * 0.45f;

    circleCenters.clear();
    colorButtons.clear();
    for (std::size_t i = 0; i < kColors.size(); ++i)
    {
        const float cx = colorPanel.position.x + colW * (static_cast<float>(i) + 0.5f);
        circleCenters.push_back(sf::Vector2f(cx, cy));

        const float btnW = colW * 0.8f;
        const float btnH = 34.f;
        colorButtons.push_back(sf::FloatRect(
            sf::Vector2f(cx - btnW / 2.f, cy + circleRadius + 20.f),
            sf::Vector2f(btnW, btnH)));
    }

    centerClock();
}

void GameFrame::handleClick(sf::Vector2f pos)
{
    for (std::size_t i = 0; i < kColors.size(); ++i)
    {
        const sf::Vector2f d = pos - circleCenters[i];
        const bool inCircle = (d.x * d.x + d.y * d.y) <= circleRadius * circleRadius;

        if (inCircle || colorButtons[i].contains(pos))
        {
            selectedColor = i;
            return;
        }
    }
}

void GameFrame::drawButton(const sf::FloatRect& rect, const std::string& label,
                      sf::Vector2f mouse, sf::Color base)
{
    const sf::Color fill = rect.contains(mouse) ? kButtonHover : base;
    window.draw(makeRect(rect, fill));

    sf::Text text(font, label, 18);
    text.setOrigin(text.getLocalBounds().getCenter());
    text.setPosition(rect.getCenter());
    window.draw(text);
}

void GameFrame::draw()
{
    const sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    window.clear(kBackground);

    // Top bar with clock
    window.draw(makeRect(clockArea, kPanel));
    window.draw(clockText);

    // Board (empty for now)
    sf::RectangleShape board = makeRect(boardRect, kBoard);
    board.setOutlineThickness(3.f);
    board.setOutlineColor(sf::Color(80, 50, 20));
    window.draw(board);

    // Player list
    window.draw(makeRect(playerPanel, kPanel));

    sf::Text header(font, "Players", 26);
    header.setPosition(sf::Vector2f(playerPanel.position.x + 15.f, playerPanel.position.y + 8.f));
    window.draw(header);

    for (std::size_t i = 0; i < players.size(); ++i)
    {
        const bool current = (i == currentPlayer);
        window.draw(makeRect(playerRows[i], current ? kHighlight : kRow));

        sf::Text name(font, (current ? "> " : "   ") + players[i], 22);
        name.setOrigin(sf::Vector2f(0.f, name.getLocalBounds().getCenter().y));
        name.setPosition(sf::Vector2f(playerRows[i].position.x + 12.f,
                                      playerRows[i].position.y + playerRows[i].size.y / 2.f));
        window.draw(name);
    }

    // Color selector (lower left)
    window.draw(makeRect(colorPanel, kPanel));

    sf::Text colorHeader(font, "Color", 26);
    colorHeader.setPosition(sf::Vector2f(colorPanel.position.x + 15.f, colorPanel.position.y + 8.f));
    window.draw(colorHeader);

    for (std::size_t i = 0; i < kColors.size(); ++i)
    {
        sf::CircleShape circle(circleRadius);
        circle.setOrigin(sf::Vector2f(circleRadius, circleRadius));
        circle.setPosition(circleCenters[i]);
        circle.setFillColor(kColors[i].color);

        if (i == selectedColor)
        {
            circle.setOutlineThickness(4.f);
            circle.setOutlineColor(sf::Color::White);
        }
        window.draw(circle);

        drawButton(colorButtons[i], i == selectedColor ? "Selected" : "Select", mouse, kButton);
    }

    window.display();
}

void GameFrame::run()
{
    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // Keep 1 unit = 1 pixel so layout math matches the window
                window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f),
                                                      sf::Vector2f(resized->size))));
                updateLayout();
            }
            else if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (click->button == sf::Mouse::Button::Left)
                    handleClick(window.mapPixelToCoords(click->position));
            }
        }

        draw();
    }
}