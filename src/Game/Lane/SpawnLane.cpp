#include "SpawnLane.h"

SpawnLane::SpawnLane()
: direction(constant::Direction::Right)
, spawnInterval(10000)
, velocity(0) {
}

void SpawnLane::setDirection(constant::Direction direction) {
    this->direction = direction;
}

void SpawnLane::setSpawnInterval(int spawnInterval) {
    this->spawnInterval = spawnInterval;
}

void SpawnLane::setVelocity(float velocity) {
    this->velocity = velocity;
}

bool SpawnLane::kill(Entity& entity) {
    for (int i = 0; i < constant::APP_COLUMN; ++i) {
        if (tiles[i].getCauseDeath() && tiles[i].collide(entity)) return true;
    }
    return false;
}

void SpawnLane::handleSpawn() {}

float SpawnLane::getVelocity() {
    return this->velocity;
}

constant::Direction SpawnLane::getDirection() {
    return this->direction;
}

bool SpawnLane::getIsActive() {
    return isActive;
}

void SpawnLane::setIsActive(bool state) {
    isActive = state;
    if (!isActive) clock.restart();
}
