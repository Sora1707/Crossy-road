#include "Tile.h"

Tile::Tile()
: isObstacle(false)
, causeDeath(false) {
}

Tile::Tile(bool isObstacle, bool causeDeath)
: isObstacle(isObstacle)
, causeDeath(causeDeath) {
}

void Tile::setIsObstacle(bool state) {
    isObstacle = state;
}

void Tile::setCauseDeath(bool state) {
    causeDeath = state;
}

bool Tile::getIsObstacle() {
    return isObstacle;
}

bool Tile::getCauseDeath() {
    return causeDeath;
}
