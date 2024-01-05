#include "Mountable.h"

Mountable::Mountable() {
    setDirection(constant::Direction::Right);
}

void Mountable::move() {
    sf::Vector2f pos = getPosition();

    using namespace constant;
    if (direction == Direction::Left) {
        pos.x -= velocity;
    }
    else if (direction == Direction::Right) {
        pos.x += velocity;
    }

    setPosition(pos);
}

