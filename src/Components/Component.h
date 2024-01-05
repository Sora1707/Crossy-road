#pragma once
#include <SFML/Graphics.hpp>
#include "../Constant.h"
#include <map>
#include <iostream>

// Abstract class for other components
class Component {
protected:
    virtual void privateMethod() = 0;

protected: 
	sf::RectangleShape box;
    sf::Text text;

// Text
public:
    void setContent(std::string content);
    void setFont(sf::Font& font);
    void setTextSize(int size);
    void setTextColor(sf::Color color);

// Box
public:
	virtual void setSize(int width, int height);
    virtual void setBackgroundColor(sf::Color color);
	virtual void setTexture(sf::Texture* texture);
    virtual void setPosition(int x, int y);

public: 
	virtual void draw(sf::RenderWindow& window);
};
