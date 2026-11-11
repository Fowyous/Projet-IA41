#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <vector>
class GameFrame
{
public:
    GameFrame();

    void run();

    // Player API (at least 2 players required)
    void setPlayers(std::vector<std::string> names);
    void setCurrentPlayer(std::size_t index);
    std::size_t getCurrentPlayer() const { return currentPlayer; }

    // Clock API
    void setClock(const std::string& time);

    // Color API
    std::size_t getSelectedColor() const { return selectedColor; }

private:
    void updateLayout();
    void centerClock();
    void handleClick(sf::Vector2f pos);
    void draw();
    void drawButton(const sf::FloatRect& rect, const std::string& label,
                    sf::Vector2f mouse, sf::Color base);

    sf::RenderWindow window;
    sf::Font font;          // must be declared before clockText
    sf::Text clockText;

    std::vector<std::string> players;
    std::size_t currentPlayer = 0;
    std::size_t selectedColor = 0;

    sf::FloatRect clockArea;
    sf::FloatRect boardRect;
    sf::FloatRect playerPanel;
    sf::FloatRect colorPanel;

    std::vector<sf::FloatRect> playerRows;
    std::vector<sf::Vector2f>  circleCenters;
    std::vector<sf::FloatRect> colorButtons;
    float circleRadius = 30.f;
};
