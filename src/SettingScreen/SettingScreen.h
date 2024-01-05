#pragma once
#include <SFML/Graphics.hpp>
#include "../Constant.h"
#include "../Components/Button.h"
#include "../Components/ImageButton.h"
#include "../Components/Label.h"
#include "../TextureHolder.h"
#include "../Game/Player.h"
#include "../Util/sfml.h"
#include <map>
#include <iostream>
#include <string>

#include "../Screen.h"

class SettingScreen: public Screen {
private:
    enum class Type {
        Up,
        Down,
        Left,
        Right,
        Volume,
        Character,
        Menu,
        Back,
        Count,
    };

    Button* buttons[(int)Type::Count];
    Label keyLabels[(int)Player::Movement::Count];
    sf::RectangleShape background;
    int isActiveId = 0;
    bool isPressed = false;

public:
    SettingScreen();
    ~SettingScreen();

public:
    void setSoundPlayer(SoundPlayer *soundPlayer) override;

public:
    // Event Handler
    void handleEvent(sf::RenderWindow &window, sf::Event &event);

    // Update
    void update(sf::RenderWindow &window);

    // draw
    void draw(sf::RenderWindow &window);

// Utility
private:
    Player::Movement getMovement(int id);
};