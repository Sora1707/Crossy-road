#pragma once
#include <SFML/Graphics.hpp>
#include "../Constant.h"
#include "Entity.h"

class Movable {
protected: 
	float velocity = 0;
    constant::Direction direction = constant::Direction::Up;

public:
	virtual void move() = 0;
	
	void setVelocity(float velocity);
	void setDirection(constant::Direction direction);

	float getVelocity();
	constant::Direction getDirection();
};