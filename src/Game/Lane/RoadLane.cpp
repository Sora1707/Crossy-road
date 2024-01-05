#include "RoadLane.h"

RoadLane::RoadLane() {
    load();
}

void RoadLane::load() {
    for (int i = 0 ; i < constant::APP_COLUMN; ++i) {
         tiles[i] = createRoad();
    }
}

void RoadLane::draw(sf::RenderWindow& window) {
    Lane::draw(window);
    for (Enemy& enemy : enemies) {
        sf::Vector2f pos = enemy.getPosition();
        enemy.setPosition(pos.x, posY);
        window.draw(enemy);
    }
}

void RoadLane::handleSpawn() {
    sf::Time time = clock.getElapsedTime();
    if (!isActive || time.asMilliseconds() >= spawnInterval) {
        clock.restart();
        enemies.push_front(enemyBase);
    }

    for (Enemy& enemy : enemies) {
        enemy.move();
    }

    if (!enemies.empty()) {
        Enemy& enemy = enemies.back();
        if (direction == constant::Direction::Right && enemy.getPosition().x >= constant::APP_WIDTH)
            enemies.pop_back();
        else if (direction == constant::Direction::Left && enemy.getPosition().x <= 0 - enemy.getSize().x)
            enemies.pop_back();
    }
    
}

void RoadLane::setEnemyBase(Enemy enemy) {
    enemyBase = enemy;
    enemyBase.setDirection(direction);
    if (enemyBase.getDirection() == constant::Direction::Left) {
         enemyBase.setPosition(constant::APP_WIDTH, posY);
    }
    else {
         enemyBase.setPosition(0 - enemyBase.getSize().x, posY);
    }
    enemyBase.setVelocity(velocity);
}

void RoadLane::spawn() {
    enemies.push_front(enemyBase);
}

bool RoadLane::kill(Entity& entity) {
    if (SpawnLane::kill(entity)) return true;
    for (Enemy& enemy : enemies) {
         if (enemy.collide(entity)) return true;
    }
    return false;
}

Tile RoadLane::createRoad() {
    int randomId = util::random(0, (int)Textures::Road::Count - 1);
    bool isObstacle = false;
    bool causeDeath = false;
    Tile tile(isObstacle, causeDeath);
    tile.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Road::StartIndex + randomId));
    tile.setSize(sf::Vector2f(constant::TILE_SIZE, constant::TILE_SIZE));
    return tile;
}


