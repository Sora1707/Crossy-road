#include "Movable.h"

void Movable::setVelocity(float velocity) {
    this->velocity = velocity;
}

void Movable::setDirection(constant::Direction direction) {
    this->direction = direction;
}

float Movable::getVelocity() {
    return this->velocity;
}

constant::Direction Movable::getDirection() {
    return this->direction;
}