#pragma once
#include <SFML/Graphics.hpp>
#include "../../Constant.h"
#include "../../Util/random.h"
#include "../../TextureHolder.h"
#include "Tile.h"

class Lane {
public:
    Lane();

public:
    bool isOutOfScreen();
    virtual void load() = 0;
    void setPosY(float posY);
    float getPosY();
    bool collide(Entity& entity);
    bool stepOn(Entity& entity);

    // Draw Tiles only
    // Other elements in each type can be handled specifically
    virtual void draw(sf::RenderWindow& window);

protected:
    Tile tiles[constant::APP_COLUMN];
    float posY;

};