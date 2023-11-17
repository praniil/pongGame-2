#include "button.h"
Button:: Button() {}
Button::Button(float x, float y, float width, float height, std::string buttonText, sf::Font& buttonFont, std::function<void()> onClickFunction)
    : onClickCallback(onClickFunction) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);

    text.setFont(buttonFont);
    text.setString(buttonText);
    text.setCharacterSize(20); // Adjust the text size as needed
    text.setFillColor(sf::Color::White);

    // Center the text inside the button
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(x + width / 2.0f, y + height / 2.0f);
    onClickCallback = onClickFunction;
}

void Button::setPosition(float x, float y) {
    shape.setPosition(x, y);

    // Update text position based on new button position
    text.setPosition(x + shape.getSize().x / 2.0f, y + shape.getSize().y / 2.0f);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(const sf::Vector2f& mousePosition) const{
    return shape.getGlobalBounds().contains(mousePosition);
}
