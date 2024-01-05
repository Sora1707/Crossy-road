#pragma once
#include <SFML/Graphics.hpp>
#include "../Constant.h"
#include "../Components/Button.h"
#include "../TextureHolder.h"
#include "../SoundHolder.h"
#include <map>
#include <iostream>

#include "../Screen.h"

class MenuScreen: public Screen {
private:
    enum class Type {
        Play,
        Setting,
        Exit,
        Count
    };

    sf::RectangleShape background;
    Button buttons[(int)Type::Count];
    int isActiveId = 0;

public:
    MenuScreen();

public:
    // Event Handler
    void handleEvent(sf::RenderWindow &window, sf::Event &event);

    // Update
    void update(sf::RenderWindow &window);

    // draw
    void draw(sf::RenderWindow &window);
};