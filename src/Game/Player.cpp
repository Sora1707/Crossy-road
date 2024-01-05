#include "Player.h"

Player& Player::getInstance() {
    static Player instance;
    return instance;
}

Player::Player()
    : isDead(false)
, isMounting(false)
, lanes(nullptr), enviVelocity(sf::Vector2f(0, 0))
, keyUp(sf::Keyboard::W)
, keyDown(sf::Keyboard::S)
, keyLeft(sf::Keyboard::A)
, keyRight(sf::Keyboard::D)
, textureId((int)Textures::Player::Left01)
{
    setVelocity(100);
    setDirection(constant::Direction::Up);
    setTexture(TextureHolder::getInstance()->getTexture(textureId + (int)constant::Direction::Up));
    setSize(sf::Vector2f(constant::PLAYER_WIDTH, constant::PLAYER_HEIGHT));

    int playerX = constant::PLAYER_START_X * constant::TILE_SIZE + constant::TILE_SIZE / 2.f - constant ::PLAYER_WIDTH / 2.f;
    int playerY = constant::PLAYER_START_Y * constant::TILE_SIZE + constant::TILE_SIZE / 2.f - constant ::PLAYER_HEIGHT / 2.f;
    setPosition(sf::Vector2f(playerX, playerY));
}

void Player::move() {

    sf::Vector2f originalPos = getPosition();
    sf::Vector2f pos         = originalPos;

    using namespace constant;
    if (direction == Direction::Left) {
        pos.x -= velocity;
    }
    else if (direction == Direction::Right) {
        pos.x += velocity;
    }
    else if (direction == Direction::Down) {
        pos.y += velocity;
    }
    else if (direction == Direction::Up) {
        pos.y -= velocity;
    }
    resetPlayerTexture();
    pos.x = (int)pos.x / TILE_SIZE * TILE_SIZE + TILE_SIZE / 2.f - PLAYER_WIDTH / 2.F;
    setPosition(pos);

    if (isOutOfScreen()) {
        setPosition(originalPos); 
        return;
    }

    if (!lanes) return;
    for (Lane* lane : *lanes) {
        if (lane->collide(*this)) {
            setPosition(originalPos);
            return;
        }
    }

    if (direction == Direction::Down) --score;
    else if (direction == Direction::Up) ++score;

    soundPlayer->addSong(Sound::PlayerMove, soundPlayer->getVolume());
}

void Player::enviMove() {
    sf::Vector2f pos = getPosition();
    pos.x += enviVelocity.x;
    pos.y += enviVelocity.y;
    setPosition(pos);
}

void Player::update() {
    bool isMounting = false;

    for (int i = 0; i < lanes->size(); ++i) {
        Lane* lane           = (*lanes)[i];
        SpawnLane* spawnLane = dynamic_cast<SpawnLane*>(lane);
        if (spawnLane) {
            if (spawnLane->kill(*this)) {
                isDead = true;
                RiverLane* riverLane = dynamic_cast<RiverLane*>(spawnLane);
                if (riverLane) {
                    soundPlayer->addSong(Sound::RiverJump, soundPlayer->getVolume());
                }
                else {
                    soundPlayer->addSong(Sound::Hit, soundPlayer->getVolume());
                }

            }
            
            RiverLane* riverLane = dynamic_cast<RiverLane*>(spawnLane);
            if (riverLane) {
                if (!isMounting && riverLane->isMounting(*this)) {
                    if (riverLane->getDirection() == constant::Direction::Left) {
                        enviVelocity.x = -riverLane->getVelocity();
                    }
                    else {
                        enviVelocity.x = riverLane->getVelocity();
                    }
                    
                    isMounting = true;

                }
            }
        }
    }
    if (!isMounting) {
        enviVelocity.x = 0;
    }
    enviMove();
}

void Player::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == event.KeyPressed) {
        using namespace constant;
        if (event.key.code == keyLeft) {
            direction = Direction::Left;
            move();
        }
        if (event.key.code == keyRight) {
            direction = Direction::Right;
            move();
        }
        if (event.key.code == keyUp) {
            direction = Direction::Up;
            move();
        }
        if (event.key.code == keyDown) {
            direction = Direction::Down;
            move();
        }
    }
}

void Player::setLanes(std::deque<Lane*>& lanes) {
    this->lanes = &lanes;
}

void Player::setIsDead(bool state) {
    this->isDead = state;
}

void Player::setIsMounting(bool state) {
    isMounting = state;
}

void Player::setEnviVelocity(sf::Vector2f velocity) {
    this->enviVelocity = velocity;
}

bool Player::getIsDead() {
    return isDead;
}

bool Player::getIsMounting() {
    return isMounting;
}

sf::Vector2f Player::getEnviVelocity() {
    return enviVelocity;
}

int Player::getScore() {
    return score;
}

void Player::setScore(int score) {
    this->score = score;
}

void Player::resetScore() {
    score = 0;
}

void Player::addScore(int value) {
    score += value;
}

void Player::setHighestScore(int score) {
    highestScore = score;
}

int Player::getHighestScore() {
    return highestScore;
}

void Player::setPlayerTextureId(int id) {
    textureId = id;
    resetPlayerTexture();
}

int Player::getPlayerTextureId() {
    return textureId;
}

void Player::resetPlayerTexture() {
    using namespace constant;
    if (direction == Direction::Left) {
        setTexture(TextureHolder::getInstance()->getTexture(textureId + (int)constant::Direction::Left));
    }
    else if (direction == Direction::Right) {
        setTexture(TextureHolder::getInstance()->getTexture(textureId + (int)constant::Direction::Right));
    }
    else if (direction == Direction::Down) {
        setTexture(TextureHolder::getInstance()->getTexture(textureId + (int)constant::Direction::Down));
    }
    else if (direction == Direction::Up) {
        setTexture(TextureHolder::getInstance()->getTexture(textureId + (int)constant::Direction::Up));
    }
}

void Player::setSoundPlayer(SoundPlayer* soundPlayer) {
    this->soundPlayer = soundPlayer;
}

void Player::setKey(Movement movement, sf::Keyboard::Key key) {
    switch (movement) {
        case Movement::Up:
            keyUp = key;
            break;
        case Movement::Down:
            keyDown = key;
            break;
        case Movement::Left:
            keyLeft = key;
            break;
        case Movement::Right:
            keyRight = key;
            break;
        default:
            std::cout << constant::ERROR << "Wrong movement\n";
    }
}

sf::Keyboard::Key Player::getKey(Movement movement) {
    sf::Keyboard::Key key;
    switch (movement) {
        case Movement::Up:
            key = keyUp;
            break;
        case Movement::Down:
            key = keyDown;
            break;
        case Movement::Left:
            key = keyLeft;
            break;
        case Movement::Right:
            key = keyRight;
            break;
        default:
            key = sf::Keyboard::Unknown;
    }
    return key;
}
