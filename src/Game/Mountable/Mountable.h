#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../Constant.h"
#include "../Movable.h"

class Mountable : public Entity, public Movable {
public:
    Mountable();
    void move() override;
};