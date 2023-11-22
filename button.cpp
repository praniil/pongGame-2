#include "button.h"
Button::Button() {}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    window.draw(text);
}

// bool Button::isClicked(const sf::Vector2f& mousePosition) const{
//     return shape.getGlobalBounds().contains(mousePosition);
// }

void Button::setButton(float x, float y, float width, float height, std::string buttonText, sf::Font &buttonFont, std::function<void()> onClickFunction)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Transparent); // Customize button color as needed

    text.setFont(buttonFont);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(x + width / 2 - text.getLocalBounds().width / 2, y + height / 2 - text.getLocalBounds().height / 2);

    onClickCallback = onClickFunction;
}

void Button::drawButton(sf::RenderWindow &window)
{
    window.draw(shape);
    window.draw(text);
}

bool Button::isButtonClicked(const sf::Vector2f &mousePosition) const
{
    return shape.getGlobalBounds().contains(mousePosition);
}
