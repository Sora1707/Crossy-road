#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "../Constant.h"
#include "../TextureHolder.h"
#include "Entity.h"
#include "Movable.h"
#include "Lane/Lane.h"
#include "Lane/SpawnLane.h"
#include "Lane/RiverLane.h"
#include "../SoundPlayer.h"

class Player : public Entity, public Movable  {

public:
    enum class Movement {
        Up,
        Down,
        Left,
        Right,
        Count,
    };
    
public: 
    static Player& getInstance();

private:
    Player();

public:
    void move() override;
    void enviMove();
    void update();
    void handleEvent(sf::RenderWindow& window, sf::Event& event);

public:
    void setLanes(std::deque<Lane*> &lanes);

    void setIsDead(bool state);
    void setIsMounting(bool state);
    void setEnviVelocity(sf::Vector2f velocity);

    bool getIsDead();
    bool getIsMounting();
    sf::Vector2f getEnviVelocity();

    int getScore();
    void setScore(int score);
    void resetScore();
    void addScore(int value);

    void setHighestScore(int score);
    int getHighestScore();

    void setPlayerTextureId(int id);
    int getPlayerTextureId();

    void resetPlayerTexture();

    void setSoundPlayer(SoundPlayer* soundPlayer);

public: 
    void setKey(Movement movement, sf::Keyboard::Key key);
    sf::Keyboard::Key getKey(Movement movement);

private:
    sf::Keyboard::Key keyUp;
    sf::Keyboard::Key keyDown;
    sf::Keyboard::Key keyLeft;
    sf::Keyboard::Key keyRight;

private:
    int textureId;

private:
    bool isDead;
    sf::Vector2f enviVelocity;
    std::deque<Lane*>* lanes;
    SoundPlayer* soundPlayer;

    bool isMounting;
    int score = 0;
    int highestScore = 0;
};