#pragma once
#include <SFML/Graphics.hpp>
#include "../../Constant.h"
#include "Lane.h"

class GrassLane: public Lane {
public:
    GrassLane();

public:
    void load() override;
    void draw(sf::RenderWindow& window) override;

private:
    Tile createObstacle();
    Tile createGrass();
};