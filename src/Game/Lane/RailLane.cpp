#include "RailLane.h"

RailLane::RailLane() {
    load();
}

void RailLane::load() {
    for (int i = 0 ; i < constant::APP_COLUMN; ++i) {
         tiles[i] = createRail();
    }
}

void RailLane::draw(sf::RenderWindow& window) {
    int offset = 5;

    if (direction == constant::Direction::Right) 
        tiles[offset].setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Rail::Traffic));
    else tiles[constant::APP_COLUMN - offset].setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Rail::Traffic)); 
    Lane::draw(window);

    for (Enemy& enemy : enemies) {
         sf::Vector2f pos = enemy.getPosition();
         enemy.setPosition(pos.x, posY);
         window.draw(enemy);
    }

    if (spawnInterval - clock.getElapsedTime().asMilliseconds() <= 1000
        && (spawnInterval - clock.getElapsedTime().asMilliseconds()) % 5 == 0) {
        /*sf::Text text;
         sf::String arrowString = direction == constant::Direction::Left ? "<===" : "===>";
        text.setString(std::string(arrowString));
        text.setCharacterSize(75);
        text.setFont(constant::fontArial);
        text.setFillColor(sf::Color::Red);
        text.setPosition(constant::APP_WIDTH / 2 - 60, posY + 10);
        window.draw(text);*/
         int id = direction == constant::Direction::Right ? offset : constant::APP_COLUMN - offset;
        tiles[id].setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Rail::TrafficActive));
        window.draw(tiles[id]);
    }
}

void RailLane::handleSpawn() {
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

void RailLane::setEnemyBase(Enemy enemy) {
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

void RailLane::spawn() {
    enemies.push_front(enemyBase);
}

bool RailLane::kill(Entity& entity) {
    if (SpawnLane::kill(entity)) return true;
    for (Enemy& enemy : enemies) {
         if (enemy.collide(entity)) return true;
    }
    return false;
}

Tile RailLane::createRail() {
    bool isObstacle = false;
    bool causeDeath = false;
    Tile tile(isObstacle, causeDeath);
    tile.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Rail::Default));
    tile.setSize(sf::Vector2f(constant::TILE_SIZE, constant::TILE_SIZE));
    return tile;
}


