#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "../../Constant.h"
#include "SpawnLane.h"
#include "../Enemy/Enemy.h"

class RoadLane: public SpawnLane {
public:
    RoadLane();

public:
    void load() override;
    void draw(sf::RenderWindow& window) override;
    void handleSpawn() override;
    void setEnemyBase(Enemy enemy);
    void spawn() override;

    bool kill(Entity& entity) override;
   
private:
    Enemy enemyBase;
    std::deque<Enemy> enemies;
    Tile createRoad();
};