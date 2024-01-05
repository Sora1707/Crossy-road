#pragma once
#include <SFML/Graphics.hpp>
#include "../../Constant.h"
#include "../Entity.h"

class Tile : public Entity {
public:
    Tile();
    Tile(bool isObstacle, bool causeDeath);

public:
    void setIsObstacle(bool state);
    void setCauseDeath(bool state);
    bool getIsObstacle();
    bool getCauseDeath();

private:
    bool isObstacle;
    bool causeDeath;
};