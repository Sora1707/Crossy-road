#include "GrassLane.h"

GrassLane::GrassLane() {
    load();
}

void GrassLane::load() {
     const int MAX_OBSTACLES = constant::APP_COLUMN / 4;

    for (int i = 0, obstacleCount = 0 ; i < constant::APP_COLUMN; ++i) {
        if (i != constant::PLAYER_START_X 
            && posY / constant::TILE_SIZE != constant::PLAYER_START_Y
            && obstacleCount < MAX_OBSTACLES 
            && util::random(0, 3) == 0) {
            ++obstacleCount;
            tiles[i] = createObstacle();
        }
        else tiles[i] = createGrass();
    }
}

void GrassLane::draw(sf::RenderWindow& window) {
    Lane::draw(window);
}

Tile GrassLane::createObstacle() {
    int randomId = util::random(0, (int)Textures::Obstacle::Count - 1);
    bool isObstacle = true;
    bool causeDeath = false;
    Tile tile(isObstacle, causeDeath);
    tile.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Obstacle::StartIndex + randomId));
    tile.setSize(sf::Vector2f(constant::TILE_SIZE, constant::TILE_SIZE));
    return tile;
}

Tile GrassLane::createGrass() {
    int randomId    = util::random(0, (int)Textures::Grass::Count - 1);
    bool isObstacle = false;
    bool causeDeath = false;
    Tile tile(isObstacle, causeDeath);
    tile.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Grass::StartIndex + randomId));
    tile.setSize(sf::Vector2f(constant::TILE_SIZE, constant::TILE_SIZE));
    return tile;
}


