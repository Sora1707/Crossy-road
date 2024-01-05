#pragma once
#include <SFML/Graphics.hpp>
#include "../Constant.h"
#include "Button.h"
#include <map>
#include <iostream>

// Abstract class for other components
class ImageButton: public Button {
private:
    sf::RectangleShape image;

// Image
public:
    void setImageTexture(sf::Texture* texture);
    void setImageSize(int width, int height);
    void setPosition(int x, int y) override;
    void draw(sf::RenderWindow& window) override;
};
