#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "../Constant.h"
#include "../Game/Player.h"
#include "../TextureHolder.h"

#include "../Game/Lane/GrassLane.h"
#include "../Game/Lane/RoadLane.h"
#include "../Game/Lane/RiverLane.h"
#include "../Game/Lane/RailLane.h"

#include "../Game/Enemy/Car.h"
#include "../Game/Enemy/Train.h"
#include "../Game/Mountable/Wood.h"

#include "../Screen.h"

class GameScreen: public Screen {
public:
    GameScreen();



    ~GameScreen();

public:
    void setStaticText();

public: 
    // Event Handler
    void handleEvent(sf::RenderWindow &window, sf::Event &event);

    // Update
    void update(sf::RenderWindow &window);

    // draw
    void draw(sf::RenderWindow &window);

public:
    void setIsPause(bool state);
    bool needNewGame();

private: 
    Lane *createRailLane(float posY);
    Lane *createRoadLane(float posY);
    Lane *createRiverLane(float posY);
    Lane *createGrassLane(float posY);
    Lane *createRandomLane(float posY);

private:
    Player& player;
    std::deque<Lane*> lanes;
    bool isPause = false;
    bool newGame = false;

private:
    sf::Text gameOverText;
    sf::Text pressEnterText;
    sf::Text scoreText;
    sf::Text highestScoreText;
};