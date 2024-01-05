#include "Wood.h"

Wood::Wood() {
    setSize(sf::Vector2f(constant::WOOD_WIDTH, constant::WOOD_HEIGHT));
    setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Mountable::Wood));
}

