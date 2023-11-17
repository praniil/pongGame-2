#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> onClickCallback;

public:
    Button();
    Button(float x, float y, float width, float height, std::string buttonText, sf::Font& buttonFont, std::function<void()> onClickFunction);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2f& mousePosition) const;
};

#endif // BUTTON_H
