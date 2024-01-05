#include "ImageButton.h"

void ImageButton::setImageTexture(sf::Texture* texture) {
    image.setTexture(texture);
}

void ImageButton::setImageSize(int width, int height) {
    image.setSize(sf::Vector2f(width, height));
}

void ImageButton::setPosition(int x, int y) {
    box.setPosition(x, y);

    float imageX = x + box.getLocalBounds().width / 2 - image.getSize().x / 2;
    float imageY = y + box.getLocalBounds().height / 2 - image.getSize().y / 2;

    image.setPosition(imageX, imageY);
}

void ImageButton::draw(sf::RenderWindow& window) {
    Button::draw(window);
    window.draw(image);
}


