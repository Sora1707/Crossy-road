#include "Car.h"

Car::Car() {
    setSize(sf::Vector2f(constant::CAR_WIDTH, constant::CAR_HEIGHT));
    setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Car::Right01));
}
