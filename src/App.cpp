#include "App.h"

App::App() {
    window.create(sf::VideoMode(constant::APP_WIDTH, constant::APP_HEIGHT), constant::APP_TITLE);
    window.setFramerateLimit(constant::APP_FPS);

    load();

    screens[(int)constant::Screen::Menu]    = std::make_shared<MenuScreen>();
    screens[(int)constant::Screen::Menu]->setSoundPlayer(&soundPlayer);

    screens[(int)constant::Screen::Setting] = std::make_shared<SettingScreen>();
    screens[(int)constant::Screen::Setting]->setSoundPlayer(&soundPlayer);

    screens[(int)constant::Screen::Game]    = std::make_shared<GameScreen>();
    screens[(int)constant::Screen::Game]->setSoundPlayer(&soundPlayer);

    currentScreenId = (int)constant::Screen::Menu;

    std::string bgmFile = "resource/music/Leap to the Beat.mp3";
    if (!bgm.openFromFile(bgmFile)) {
        std::cout << constant::ERROR << "Cannot open file " << bgmFile << "\n";
        window.close();
        return;
    }
    bgm.setLoop(true);
    bgm.setVolume(50);
}

App::~App() {
}

void App::run() {
    TextureHolder* textureHolder = TextureHolder::getInstance();
    SoundHolder& soundHolder      = SoundHolder::getInstance();
    Player& player               = Player::getInstance();

    player.setSoundPlayer(&soundPlayer);

    bgm.play();

    soundPlayer.addSong(Sound::Train);
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }

    save();

    std::cout << constant::INFO << "App closing...\n";
}

void App::close() {
    window.close();
}

void App::save() {
    saveSetting();
    savePlayer();
    saveTiles();
}

void App::load() {
    loadSetting();
    loadPlayer();
    loadTiles();
}

void App::saveSetting() {
    // volume
    std::ofstream output;
    output.open(constant::SAVED_SETTING_FILE);
    if (!output) {
        std::cout << constant::ERROR << "Cannot open " << constant::SAVED_SETTING_FILE << "\n";
        output.close();
        return;
    }

    output << soundPlayer.getVolume() << '\n';

    output.close();
}

void App::savePlayer() {
    // score
    // highestScore
    // textureId
    std::ofstream output;
    output.open(constant::SAVED_PLAYER_FILE);
    if (!output) {
        std::cout << constant::ERROR << "Cannot open " << constant::SAVED_PLAYER_FILE << "\n";
        output.close();
        return;
    }

    Player& player = Player::getInstance();
    output << player.getScore() << '\n';
    output << player.getHighestScore() << '\n';
    output << player.getPlayerTextureId() << '\n';
    output.close();
}

void App::saveTiles() {
}

void App::loadSetting() {
    // volume
    std::ifstream input;
    input.open(constant::SAVED_SETTING_FILE);
    if (!input) {
        std::cout << constant::ERROR << "Cannot open " << constant::SAVED_SETTING_FILE << "\n";
        input.close();
        return;
    }

    float volume;
    input >> volume;
    soundPlayer.setVolume(volume);

    input.close();
}

void App::loadPlayer() {
    // score
    // highestScore
    // textureId
    std::ifstream input;
    input.open(constant::SAVED_PLAYER_FILE);
    if (!input) {
        std::cout << constant::ERROR << "Cannot open " << constant::SAVED_PLAYER_FILE << "\n";
        input.close();
        return;
    }

    Player& player = Player::getInstance();

    int score, highestScore, playerTextureId;

    input >> score >> highestScore >> playerTextureId;
    player.setScore(score);
    player.setHighestScore(highestScore);
    player.setPlayerTextureId(playerTextureId);
    input.close();
}

void App::loadTiles() {
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            break;
        }
        screens[currentScreenId]->handleEvent(window, event);
    }
}

void App::update() {
    // soundPlayer.handlePlayer();

    if (screens[currentScreenId]->getIsExit()) close();

    screens[currentScreenId]->update(window);

    int isActiveId = screens[currentScreenId]->getCurrentScreenId();

    std::shared_ptr<GameScreen> tmpGameScreen = std::dynamic_pointer_cast<GameScreen>(screens[isActiveId]);
    if (tmpGameScreen) {
        if (tmpGameScreen->needNewGame()) {
            
            std::cout << constant::INFO << "Start a new game\n";
            Player& player = Player::getInstance();
            player.setIsDead(false);

            int newHighestScore = std::max(player.getHighestScore(), player.getScore());
            std::cout << newHighestScore << "\n";
            player.setHighestScore(newHighestScore);

            tmpGameScreen = std::make_shared<GameScreen>();
            tmpGameScreen->setIsPause(false);
            tmpGameScreen->setSoundPlayer(&soundPlayer);

            screens[isActiveId] = tmpGameScreen;
        }
    }

    if (currentScreenId == isActiveId) return;

    /* CHANGE SCREEN */
    // Set the current screen back to its state
    screens[currentScreenId]->setCurrentScreenId(currentScreenId);

    // Set the previous screen of the currently active screen
    screens[isActiveId]->setPrevScreenId(currentScreenId);

    // Change to the currently active screen
    currentScreenId = isActiveId;

    
    if (tmpGameScreen) {
        tmpGameScreen->setIsPause(false);
    }
}

// Render
void App::render() {
    window.clear(constant::BLACK);

    screens[currentScreenId]->draw(window);

    window.display();
}
