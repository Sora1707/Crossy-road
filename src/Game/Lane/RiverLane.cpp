#include "RiverLane.h"

RiverLane::RiverLane() {
    load();
}

void RiverLane::load() {
    for (int i = 0 ; i < constant::APP_COLUMN; ++i) {
         tiles[i] = createRiver();
    }
}

void RiverLane::draw(sf::RenderWindow& window) {
    Lane::draw(window);
    for (Mountable& mountable : mountables) {
         sf::Vector2f pos = mountable.getPosition();
         mountable.setPosition(pos.x, posY);
         window.draw(mountable);
    }
}

void RiverLane::handleSpawn() {
    sf::Time time = clock.getElapsedTime();
    if (!isActive || time.asMilliseconds() >= spawnInterval) {
         clock.restart();
         mountables.push_front(mountableBase);
    }

    for (Mountable& mountable : mountables) {
         mountable.move();
    }

    if (!mountables.empty()) {
         Mountable& mountable = mountables.back();
         if (direction == constant::Direction::Right && mountable.getPosition().x >= constant::APP_WIDTH)
             mountables.pop_back();
         else if (direction == constant::Direction::Left && mountable.getPosition().x <= 0 - mountable.getSize().x)
             mountables.pop_back();
    }
}

void RiverLane::setMountableBase(Mountable mountable) {
    mountableBase = mountable;
    mountableBase.setDirection(direction);
    if (mountableBase.getDirection() == constant::Direction::Left) {
         mountableBase.setPosition(constant::APP_WIDTH, posY);
    }
    else {
         mountableBase.setPosition(0 - mountableBase.getSize().x, posY);
    }
    mountableBase.setVelocity(velocity);
}

void RiverLane::spawn() {
    mountables.push_front(mountableBase);
}

bool RiverLane::kill(Entity& entity) {
    if (!stepOn(entity)) return false;
    return !isMounting(entity);
}

bool RiverLane::isMounting(Entity& entity) {
    for (Mountable& mountable : mountables) {
         if (mountable.collide(entity)) return true;
    }
    return false;
}

Tile RiverLane::createRiver() {
    bool isObstacle = false;
    bool causeDeath = true;
    Tile tile(isObstacle, causeDeath);
    tile.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::River::Default));
    tile.setSize(sf::Vector2f(constant::TILE_SIZE, constant::TILE_SIZE));
    return tile;
}

Tile RiverLane::createLilyPad() {
    bool isObstacle = false;
    bool causeDeath = false;
    Tile tile(isObstacle, causeDeath);
    tile.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::River::LilyPad));
    tile.setSize(sf::Vector2f(constant::TILE_SIZE, constant::TILE_SIZE));
    return tile;
}


