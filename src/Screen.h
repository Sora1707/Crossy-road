#pragma once
#include <SFML/Graphics.hpp>
#include "Constant.h"
#include "TextureHolder.h"
#include "SoundPlayer.h"

class Screen {
public:
    Screen();
    virtual ~Screen();

public: 
    virtual void handleEvent(sf::RenderWindow &window, sf::Event &event) = 0;
    virtual void update(sf::RenderWindow &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

public:
    virtual void setCurrentScreenId(int id);
    virtual int getCurrentScreenId();

    virtual void setPrevScreenId(int id);
    virtual int getPrevScreenId();

    virtual void setIsExit(bool state);
    virtual bool getIsExit();

    virtual void setSoundPlayer(SoundPlayer *soundPlayer);

protected:
    SoundPlayer *soundPlayer;

protected:
    bool isExit = false;
    int currentScreenId = 0;
    int prevScreenId = 0;
};