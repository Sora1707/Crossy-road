#include "Component.h"

void Component::setContent(std::string content) {
    text.setString(content);
}

void Component::setFont(sf::Font& font) {
    text.setFont(font);
}

void Component::setTextSize(int size) {
    text.setCharacterSize(size);
}

void Component::setTextColor(sf::Color color) {
    text.setFillColor(color);
}

void Component::setSize(int width, int height) {
    box.setSize(sf::Vector2f(width, height));
}

void Component::setBackgroundColor(sf::Color color) {
    box.setFillColor(color);
}

void Component::setTexture(sf::Texture* texture) {
    box.setTexture(texture);
}

void Component::setPosition(int x, int y) {
    box.setPosition(x, y);

    float textX = x + box.getLocalBounds().width / 2 - text.getLocalBounds().width / 2;
    float textY = y + box.getLocalBounds().height / 2 - text.getLocalBounds().height / 1.5;

    text.setPosition(textX, textY);
}

void Component::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}
