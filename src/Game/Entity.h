#pragma once
#include <SFML/Graphics.hpp>
#include "../Constant.h"

class Entity : public sf::RectangleShape {
public: 
    bool collide(Entity &other);
    bool isOutOfScreen();

private:
    
};