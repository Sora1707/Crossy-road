#include "GameScreen.h"

GameScreen::GameScreen(): player(Player::getInstance()) {
    isPause = true;

    setCurrentScreenId((int)constant::Screen::Game);

    //lanes.push_back(createRailLane(0 * constant::TILE_SIZE));
    for (int i = 0; i < constant::APP_ROW - constant::APP_SAFE_LANE; ++i) {
        lanes.push_back(createRandomLane(i * constant::TILE_SIZE));
    }

    for (int i = constant::APP_ROW - constant::APP_SAFE_LANE; i < constant::APP_ROW + 1; ++i) {
        lanes.push_back(createGrassLane(i * constant::TILE_SIZE));
    }

    setStaticText();

    // Player setting
    sf::Vector2f enviVelocity = player.getEnviVelocity();
    enviVelocity.y            = constant::APP_VELOCITY;
    player.setEnviVelocity(enviVelocity);
    player.setIsMounting(false);
    player.setLanes(lanes);
    player.setDirection(constant::Direction::Up);

    int playerX = constant::PLAYER_START_X * constant::TILE_SIZE + constant::TILE_SIZE / 2.f - constant ::PLAYER_WIDTH / 2.f;
    int playerY = constant::PLAYER_START_Y * constant::TILE_SIZE + constant::TILE_SIZE / 2.f - constant ::PLAYER_HEIGHT / 2.f;
    player.setPosition(sf::Vector2f(playerX, playerY));

    player.resetScore();

}

GameScreen::~GameScreen(){
    std::cout << constant::INFO << "Game Screen destructor\n";
    while (!lanes.empty()) {
        Lane* lane = lanes.back();
        lanes.pop_back();
        delete lane;
    }
    std::cout << constant::INFO << "Game Screen finished deallocation\n";
}

void GameScreen::setStaticText(){
    gameOverText.setString(std::string("Game Over"));
    gameOverText.setCharacterSize(100);
    gameOverText.setFont(constant::fontArial);
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setPosition(constant::APP_WIDTH / 2 - gameOverText.getLocalBounds().width / 2, 200);

    pressEnterText.setString(std::string("Press Enter to continue..."));
    pressEnterText.setCharacterSize(50);
    pressEnterText.setFont(constant::fontArial);
    pressEnterText.setFillColor(sf::Color::Black);
    pressEnterText.setPosition(constant::APP_WIDTH / 2 - gameOverText.getLocalBounds().width / 2, 400);

    scoreText.setCharacterSize(50);
    scoreText.setFont(constant::fontArial);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(10, 10);

    highestScoreText.setCharacterSize(50);
    highestScoreText.setFont(constant::fontArial);
    highestScoreText.setFillColor(sf::Color::Red);
    highestScoreText.setPosition(1300, 10);
};    

void GameScreen::handleEvent(sf::RenderWindow& window, sf::Event& event) {

    if (event.type == event.KeyPressed) {
        if (player.getIsDead()) {
            if (event.key.code == sf::Keyboard::Enter) {
                newGame = true;
            }
            return;
        }

        if (event.key.code == sf::Keyboard::Escape) {
            soundPlayer->addSong(Sound::ButtonEnter, soundPlayer->getVolume());
            setIsPause(true);
            setCurrentScreenId((int)constant::Screen::Setting);
        }
    }

    if (isPause) return;

    player.handleEvent(window, event);
}

void GameScreen::update(sf::RenderWindow& window) {

    if (player.isOutOfScreen()) {
        if (!player.getIsDead())
            soundPlayer->addSong(Sound::RiverFlow, soundPlayer->getVolume());
        player.setIsDead(true);
    }
    if (player.getIsDead()) return;

    // Pause handle
    for (Lane* lane : lanes) {
        SpawnLane* spawnLane = dynamic_cast<SpawnLane*>(lane);
        if (spawnLane) {
            spawnLane->setIsActive(!isPause);
        }
    }

    if (isPause) return;

     float worldVelocity;
    if (player.getPosition().y >= constant::APP_HEIGHT * 0.5f) worldVelocity = constant::APP_VELOCITY;
    else worldVelocity = constant::APP_SPEEDUP_VELOCITY;

    // Generate new road
    if (lanes.back()->isOutOfScreen()) {
        float delayPixels = lanes.back()->getPosY() - constant::APP_HEIGHT;
        delete lanes.back();
        lanes.pop_back();
        lanes.push_front(createRandomLane(-constant::TILE_SIZE + delayPixels));
    }
    
    // Moving the world
    sf::Vector2f enviVelocity = player.getEnviVelocity();
    enviVelocity.y            = worldVelocity;
    player.setEnviVelocity(enviVelocity);

    for (Lane* lane : lanes) {
        float posY = lane->getPosY();
        lane->setPosY(posY + worldVelocity);
    }

    // Spawn handle
    for (Lane* lane : lanes) {
        SpawnLane* spawnLane = dynamic_cast<SpawnLane*>(lane);
        if (spawnLane) {
            spawnLane->handleSpawn();
        }
    }

    // Player
    player.update();
}

void GameScreen::draw(sf::RenderWindow& window) {

    for (Lane* lane : lanes) {
        lane->draw(window);
    }

    window.draw(player);

    scoreText.setString(std::string(std::to_string(player.getScore())));
    window.draw(scoreText);

    highestScoreText.setString("Highest: " + std::string(std::to_string(player.getHighestScore())));
    window.draw(highestScoreText);

    if (player.getIsDead()) {
        window.draw(gameOverText);
        window.draw(pressEnterText);
        return;
    }
}

void GameScreen::setIsPause(bool state) {
    isPause = state;
}

bool GameScreen::needNewGame() {
    return newGame;
}

Lane* GameScreen::createRailLane(float posY) {
    int randomValue               = util::random(0, 1);
    constant::Direction direction;
    Train train;
    if (randomValue == 0) {
        direction = constant::Direction::Left;
        train.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Train::Left));
    }
    else {
        direction = constant::Direction::Right;
        train.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Train::Right));
    }
    RailLane* railLane = new RailLane();
    int velocity       = util::random(50, 50);
    int spawnInterval  = util::random(30, 50) * 100;
    railLane->setDirection(direction);
    railLane->setPosY(posY);
    railLane->setVelocity(velocity);
    railLane->setSpawnInterval(spawnInterval);
    railLane->setEnemyBase(train);
    railLane->spawn();
    return railLane;
}

Lane* GameScreen::createRoadLane(float posY) {
    int directionRandomValue        = util::random(0, 1);
    int textureRandomValue          = util::random(0, 4);
    constant::Direction direction;
    Car car;
    if (directionRandomValue == 0) {
        direction = constant::Direction::Left;
        car.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Car::Left01 + textureRandomValue));
    }
    else {
        direction = constant::Direction::Right;
        car.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Car::Right01 + textureRandomValue));
    }
    int velocity = util::random(5, 10);
    int spawnInterval = util::random(15, 20) * 100;
    RoadLane* roadLane = new RoadLane();
    roadLane->setDirection(direction);
    roadLane->setPosY(posY);
    roadLane->setVelocity(velocity);
    roadLane->setSpawnInterval(spawnInterval);
    roadLane->setEnemyBase(car);
    roadLane->spawn();

    return roadLane;
}

Lane* GameScreen::createRiverLane(float posY) {
    int randomValue = util::random(0, 1);
    constant::Direction direction;
    Wood wood;
    if (randomValue == 0) {
        direction = constant::Direction::Left;
    }
    else {
        direction = constant::Direction::Right;
    }
    int velocity      = util::random(5, 10);
    int spawnInterval = util::random(10, 20) * 100;
    RiverLane* riverLane = new RiverLane();
    riverLane->setDirection(direction);
    riverLane->setPosY(posY);
    riverLane->setVelocity(velocity);
    riverLane->setSpawnInterval(spawnInterval);
    riverLane->setMountableBase(wood);
    riverLane->spawn();

    return riverLane;
}

Lane* GameScreen::createGrassLane(float posY) {
    GrassLane* lane = new GrassLane();
    lane->setPosY(posY);
    return lane;
}

Lane* GameScreen::createRandomLane(float posY) {
    /*
    Rail:  10%
    River: 20%
    Road:  30%
    Grass: 40%
    */

    int type = util::random(1, 10);
    if (1 <= type && type <= 1) return createRailLane(posY);
    if (2 <= type && type <= 3) return createRiverLane(posY);
    if (4 <= type && type <= 6) return createRoadLane(posY);
    return createGrassLane(posY);
    
}
