#include "Enemy.h"

Enemy::Enemy() {
    setDirection(constant::Direction::Right);
}

void Enemy::move() {
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

