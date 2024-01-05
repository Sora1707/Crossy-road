#include "MenuScreen.h"

MenuScreen::MenuScreen() {
    setCurrentScreenId((int)constant::Screen::Menu);

    int startY = 350;

    background.setSize(sf::Vector2f(constant::APP_WIDTH, constant::APP_HEIGHT));
    background.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Background::Main));

    for (int i = 0; i < (int)Type::Count; ++i) {
        buttons[i].setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Normal));
        buttons[i].setSize(constant::BUTTON_WIDTH, constant::BUTTON_HEIGHT);
        buttons[i].setFont(constant::fontArial);
        buttons[i].setTextSize(25);
    }

    buttons[(int)Type::Play].setContent("Play");
    buttons[(int)Type::Setting].setContent("Setting");
    buttons[(int)Type::Exit].setContent("Exit");

    for (int i = 0; i < (int)Type::Count; ++i) {
        buttons[i].setPosition(constant::APP_WIDTH / 2 - constant::BUTTON_WIDTH / 2, startY + 75 * i);
    }

}


void MenuScreen::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    SoundHolder& soundHolder = SoundHolder::getInstance();

    // Key pressed events
    if (event.type == event.KeyPressed) {
        if (event.key.code == sf::Keyboard::Down) {
            soundPlayer->addSong(Sound::ButtonMove, soundPlayer->getVolume());
            isActiveId = (isActiveId + 1) % (int)Type::Count;
        }
        else if (event.key.code == sf::Keyboard::Up) {
            soundPlayer->addSong(Sound::ButtonMove, soundPlayer->getVolume());
            isActiveId = (isActiveId - 1 + (int)Type::Count) % (int)Type::Count;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            soundPlayer->addSong(Sound::ButtonEnter, soundPlayer->getVolume());
            if (isActiveId == (int)Type::Play) setCurrentScreenId((int)constant::Screen::Game);
            if (isActiveId == (int)Type::Setting) setCurrentScreenId((int)constant::Screen::Setting);
            if (isActiveId == (int)Type::Exit) setIsExit(true);
        }
    }

    // Mouse events
    /*if (buttons[(int)Type::Play].isClicked(window)) setCurrentScreenId((int)constant::Screen::Game);
    if (buttons[(int)Type::Play].isClicked(window)) setCurrentScreenId((int)constant::Screen::Setting);
    if (buttons[(int)Type::Exit].isClicked(window)) exit(0);*/
}

void MenuScreen::update(sf::RenderWindow& window) {
    buttons[isActiveId].setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Active));

    for (int i = 0; i < (int)Type::Count; ++i) {
        if (buttons[i].isHovered(window)) buttons[i].setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Hovered));
        else if (i != isActiveId) buttons[i].setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Normal));
        else buttons[i].setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Active));
    }

}

void MenuScreen::draw(sf::RenderWindow& window) {
    window.draw(background);
    for (Button& button : buttons) {
        button.draw(window);
    }
}
