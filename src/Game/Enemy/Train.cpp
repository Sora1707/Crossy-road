#include "Train.h"

Train::Train() {
    setSize(sf::Vector2f(constant::TRAIN_WIDTH, constant::TRAIN_HEIGHT));
    setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Train::Right));
}
