#pragma once
#include <SFML/Graphics.hpp>
#include "../Constant.h"
#include "Component.h"
#include <map>
#include <iostream>

// Abstract class for other components
class Button: public Component {
protected:
    void privateMethod() override {}

protected:
    void (*handler)() = []() { std::cout << "Default handler\n"; };

// Click
public:
    bool isClicked(sf::RenderWindow& window);
    void click();
    void click(void (*handler)());
    void setHandler(void (*handler)());

// Hover
    bool isHovered(sf::RenderWindow& window);

};
