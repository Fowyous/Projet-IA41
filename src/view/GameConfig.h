#include <SFML/Graphics.hpp>
#include <string>
namespace GameConfig
{
    const std::string kFontPath = "src/view/AdwaitaMono-BoldItalic.ttf";

    const sf::Color kBackground(30, 30, 30);
    const sf::Color kPanel(45, 45, 50);
    const sf::Color kRow(60, 60, 68);
    const sf::Color kHighlight(70, 130, 180);
    const sf::Color kButton(70, 130, 180);
    const sf::Color kButtonHover(100, 160, 220);
    const sf::Color kBoard(139, 90, 43);

    struct ColorOption
    {
        std::string name;
        sf::Color   color;
    };

    const std::vector<ColorOption> kColors = {
        {"Red",    sf::Color(220,  50,  50)},
        {"Blue",   sf::Color( 50, 100, 220)},
        {"Green",  sf::Color( 50, 180,  80)},
        {"Yellow", sf::Color(240, 210,  50)}
    };

    // Helper: a filled rectangle at the given rect
    sf::RectangleShape makeRect(const sf::FloatRect& rect, sf::Color fill)
    {
        sf::RectangleShape shape;
        shape.setPosition(rect.position);
        shape.setSize(rect.size);
        shape.setFillColor(fill);
        return shape;
    }
}