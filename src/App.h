#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constant.h"
#include "GameScreen/GameScreen.h"
#include "MenuScreen/MenuScreen.h"
#include "SettingScreen/SettingScreen.h"
#include "TextureHolder.h"
#include "SoundHolder.h"
#include "SoundPlayer.h"
#include <fstream>

class App {
public:
    App();
    ~App();

public: 
    void run();
    void close();
    void save();
    void load();

private:
    void saveSetting();
    void savePlayer();
    void saveTiles();

private:
    void loadSetting();
    void loadPlayer();
    void loadTiles();

private:
    sf::RenderWindow window;
    SoundPlayer soundPlayer;

private:
    int currentScreenId;
    std::shared_ptr<Screen> screens[(int)constant::Screen::Count];

    sf::Music bgm;

private:
    void processEvents();
    void update();
    void render();
};