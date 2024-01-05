#pragma once
#include <SFML/Graphics.hpp>
#include "../../Constant.h"
#include "../../Util/random.h"
#include "../../TextureHolder.h"
#include "Lane.h"

class SpawnLane: public Lane {
public:
    SpawnLane();

public:
    void setDirection(constant::Direction direction);
    void setSpawnInterval(int spawnInterval);
    void setVelocity(float velocity);

    virtual bool kill(Entity& entity);
    virtual void handleSpawn() = 0;
    virtual void spawn() = 0;

    float getVelocity();
    constant::Direction getDirection();

    bool getIsActive();
    void setIsActive(bool state);

protected:
    sf::Clock clock;
    int spawnInterval; // milliseconds
    float velocity;
    constant::Direction direction;
    bool isActive = true;
};