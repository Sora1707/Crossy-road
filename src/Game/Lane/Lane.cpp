#include "Lane.h"

Lane::Lane() {
    posY = 0.f;
}

bool Lane::isOutOfScreen() {
    return posY >= constant::APP_HEIGHT;
}

void Lane::setPosY(float posY) {
    this->posY = posY;
}

float Lane::getPosY() {
    return this->posY;
}

bool Lane::collide(Entity& entity) {
    for (int i = 0; i < constant::APP_COLUMN; ++i) {
        if (tiles[i].getIsObstacle() && tiles[i].collide(entity)) return true;
    }
    return false;
}

bool Lane::stepOn(Entity& entity) {
    for (int i = 0; i < constant::APP_COLUMN; ++i) {
        if (tiles[i].collide(entity)) return true;
    }
    return false;
}

void Lane::draw(sf::RenderWindow& window) {
    for (int i = 0; i < constant::APP_COLUMN; ++i) {
        tiles[i].setPosition(i * constant::TILE_SIZE, posY);
        window.draw(tiles[i]);
    }
}
