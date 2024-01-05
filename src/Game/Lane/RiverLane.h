#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "../../Constant.h"
#include "SpawnLane.h"
#include "../Mountable/Mountable.h"

class RiverLane: public SpawnLane {
public:
    RiverLane();

public:
    void load() override;
    void draw(sf::RenderWindow& window) override;
    void handleSpawn() override;
    void setMountableBase(Mountable mountable);
    void spawn() override;

    bool kill(Entity& entity) override;
    bool isMounting(Entity& entity);

private:
    Mountable mountableBase;
    std::deque<Mountable> mountables;
    Tile createRiver();
    Tile createLilyPad();
};