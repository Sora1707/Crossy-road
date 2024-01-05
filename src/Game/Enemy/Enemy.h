#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../Constant.h"
#include "../Movable.h"
#include "../Entity.h"

class Enemy : public Entity, public Movable {
public:
    Enemy();
    void move() override;
};