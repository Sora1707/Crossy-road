#include "Entity.h"

bool Entity::collide(Entity& other) {
    sf::FloatRect thisRect(getPosition(), getSize());
    sf::FloatRect otherRect(other.getPosition(), other.getSize());
    return thisRect.intersects(otherRect);
}

bool Entity::isOutOfScreen() {
    sf::Vector2f pos = getPosition();
    sf::Vector2f size = getSize();
    if (pos.x + size.x < 0 || constant::APP_WIDTH < pos.x) return true;
    if (pos.y + size.y < 0 || constant::APP_HEIGHT < pos.y) return true;
    return false;
}
