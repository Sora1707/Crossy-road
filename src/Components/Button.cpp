#include "Button.h"

bool Button::isClicked(sf::RenderWindow& window) {
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isHovered(window));
}


void Button::click() {
    handler();
}

void Button::click(void (*handler)()) {
    handler();
}

void Button::setHandler(void (*handler)()) {
    this->handler = handler;
}

bool Button::isHovered(sf::RenderWindow& window) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX   = box.getPosition().x;
    float btnPosY   = box.getPosition().y;
    float btnWidth  = box.getLocalBounds().width;
    float btnHeight = box.getLocalBounds().height;
    return (
        btnPosX < mouseX && mouseX < btnPosX + btnWidth && btnPosY < mouseY && mouseY < btnPosY + btnHeight
    );
}
