#include "SettingScreen.h"

SettingScreen::SettingScreen() {
    setCurrentScreenId((int)constant::Screen::Setting);

    int startY = 100;

    Player& player = Player::getInstance();

    background.setSize(sf::Vector2f(constant::APP_WIDTH, constant::APP_HEIGHT));
    background.setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Background::Main));

    ImageButton* characterButton = new ImageButton();
    characterButton->setImageTexture(TextureHolder::getInstance()->getTexture(player.getPlayerTextureId() + (int)constant::Direction::Down));
    characterButton->setSize(constant::CHARACTER_BUTTON_WIDTH, constant::CHARACTER_BUTTON_HEIGHT);
    characterButton->setImageSize(constant::PLAYER_WIDTH * 1.8f, constant::PLAYER_HEIGHT * 1.8f);
    characterButton->setPosition(constant::APP_WIDTH / 2 - constant::CHARACTER_BUTTON_WIDTH / 2, startY);

    for (int i = 0; i < (int)Type::Count; ++i) {
        if (i == (int)Type::Character) buttons[i] = characterButton;
        else buttons[i] = new Button();
    }

    for (int i = 0; i < (int)Type::Count; ++i) {
        if (i == (int)Type::Character) continue;
        buttons[i]->setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Normal));
        buttons[i]->setSize(constant::BUTTON_WIDTH, constant::BUTTON_HEIGHT);
        buttons[i]->setFont(constant::fontArial);
        buttons[i]->setTextSize(25);
    }

    for (int i = 0; i < (int)Player::Movement::Count; ++i) {
        keyLabels[i].setBackgroundColor(sf::Color::Transparent);
        keyLabels[i].setTextColor(sf::Color::White);
        keyLabels[i].setSize(constant::BUTTON_WIDTH, constant::BUTTON_HEIGHT);
        keyLabels[i].setFont(constant::fontArial);
        keyLabels[i].setTextSize(25);
    }
    
    // Key bind
    buttons[(int)Type::Up]->setContent("Up");
    buttons[(int)Type::Down]->setContent("Down");
    buttons[(int)Type::Left]->setContent("Left");
    buttons[(int)Type::Right]->setContent("Right");

    keyLabels[(int)Player::Movement::Up].setContent(sfml::toString(player.getKey(Player::Movement::Up)));
    keyLabels[(int)Player::Movement::Down].setContent(sfml::toString(player.getKey(Player::Movement::Down)));
    keyLabels[(int)Player::Movement::Left].setContent(sfml::toString(player.getKey(Player::Movement::Left)));
    keyLabels[(int)Player::Movement::Right].setContent(sfml::toString(player.getKey(Player::Movement::Right)));

    buttons[(int)Type::Volume]->setContent("Volume: 100%");
    
    buttons[(int)Type::Menu]->setContent("Main menu");
    buttons[(int)Type::Back]->setContent("Back");

    // Set Position
    for (int i = 0; i < (int)Type::Count; ++i) {
        float posY = i <= (int)Type::Character ? 
            startY + 75 * i : 
            startY + 75 * i + constant::CHARACTER_BUTTON_WIDTH - 50;
        buttons[i]->setPosition(constant::APP_WIDTH / 2 - constant::BUTTON_WIDTH / 2, posY);
    }
    for (int i = 0; i < (int)Player::Movement::Count; ++i) {
        keyLabels[i].setTextColor(sf::Color::Black);
        keyLabels[i].setPosition(constant::APP_WIDTH / 2 - constant::BUTTON_WIDTH / 2 + 200, startY + 75 * i);
    }

}

SettingScreen::~SettingScreen() {
    for (Button* button : buttons) delete button;
}

void SettingScreen::setSoundPlayer(SoundPlayer* soundPlayer) {
    Screen::setSoundPlayer(soundPlayer);
    buttons[(int)Type::Volume]->setContent("Volume: " + std::to_string((int)soundPlayer->getVolume()) + "%");
}

void SettingScreen::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    Player& player = Player::getInstance();

    if (event.type == event.KeyPressed) {
        sf::Keyboard::Key& key = event.key.code;

        Player::Movement movement = getMovement(isActiveId);

        // Key bind
        if (isPressed && ((int)Type::Up <= isActiveId && isActiveId <= (int)Type::Right)) {

            soundPlayer->addSong(Sound::ButtonMove, soundPlayer->getVolume());

            keyLabels[isActiveId].setContent(sfml::toString(key));
            player.setKey(movement, key);
            for (int i = (int)Type::Up; i <= (int)Type::Right; ++i) {
                if (i == isActiveId) continue;
                if (key != player.getKey(getMovement(i))) continue;
                player.setKey(getMovement(i), sf::Keyboard::Unknown);
                keyLabels[i].setContent(sfml::toString(sf::Keyboard::Unknown));
            }
            isPressed = false;
        }
        else if (isPressed && isActiveId == (int)Type::Volume) {
            if (key == sf::Keyboard::Enter || key == sf::Keyboard::Escape) {
                isPressed = false;
                soundPlayer->addSong(Sound::ButtonEnter, soundPlayer->getVolume());
            }
            else if (key == sf::Keyboard::Left) {
                std::cout << "here";
                int volume = soundPlayer->getVolume();
                if (volume - 10 >= 0) volume -= 10;

                buttons[(int)Type::Volume]->setContent("Volume: " + std::to_string(volume) + '%');

                soundPlayer->setVolume(volume);
                soundPlayer->addSong(Sound::ButtonMove, volume);
            }
            else if (key == sf::Keyboard::Right) {
                int volume = soundPlayer->getVolume();
                if (volume + 10 <= 100) volume += 10;

                buttons[(int)Type::Volume]->setContent("Volume: " + std::to_string(volume) + '%');

                soundPlayer->setVolume(volume);
                soundPlayer->addSong(Sound::ButtonMove, volume);
            }
        }
        else if (isPressed && isActiveId == (int)Type::Character) {
            int textureId = player.getPlayerTextureId();
            textureId -= (int)Textures::Player::StartIndex;
            if (key == sf::Keyboard::Enter || key == sf::Keyboard::Escape) {
                isPressed = false;
                soundPlayer->addSong(Sound::ButtonEnter, soundPlayer->getVolume());
            }
            else if (key == sf::Keyboard::Left) {
                textureId = (textureId - 4 + constant::PLAYER_SPRITES * 4) % (constant::PLAYER_SPRITES * 4);
                soundPlayer->addSong(Sound::ButtonMove, soundPlayer->getVolume());
            }
            else if (key == sf::Keyboard::Right) {
                textureId = (textureId + 4) % (constant::PLAYER_SPRITES * 4);
                soundPlayer->addSong(Sound::ButtonMove, soundPlayer->getVolume());
            }
            textureId += (int)Textures::Player::StartIndex;
            player.setPlayerTextureId(textureId);
            ImageButton* characterButton = dynamic_cast<ImageButton*>(buttons[(int)Type::Character]);
            if (characterButton) {
                characterButton->setImageTexture(TextureHolder::getInstance()->getTexture(textureId + (int)constant::Direction::Down));
            }
        }
        else {
            if (key == sf::Keyboard::Down) {
                isActiveId = (isActiveId + 1) % (int)Type::Count;
                soundPlayer->addSong(Sound::ButtonMove, soundPlayer->getVolume());
            }
            else if (key == sf::Keyboard::Up) {
                isActiveId = (isActiveId - 1 + (int)Type::Count) % (int)Type::Count;
                soundPlayer->addSong(Sound::ButtonMove, soundPlayer->getVolume());
            }
            else if (key == sf::Keyboard::Enter) {
                soundPlayer->addSong(Sound::ButtonEnter, soundPlayer->getVolume());
                if (isActiveId == (int)Type::Menu) setCurrentScreenId((int)constant::Screen::Menu);
                else if (isActiveId == (int)Type::Back) setCurrentScreenId(getPrevScreenId());
                else isPressed = true;
            }
        }
    }
}

void SettingScreen::update(sf::RenderWindow& window) {
    buttons[isActiveId]->setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Active));

    for (int i = 0; i < (int)Type::Count; ++i) {
        if (buttons[i]->isHovered(window)) buttons[i]->setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Hovered));
        else if (i != isActiveId) buttons[i]->setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Normal));
        else if (!isPressed) buttons[i]->setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Active));
        else buttons[i]->setTexture(TextureHolder::getInstance()->getTexture((int)Textures::Button::Hovered));
    }
}

void SettingScreen::draw(sf::RenderWindow& window) {
    window.draw(background);
    for (Button* button : buttons) {
        button->draw(window);
    }
    for (Label& label: keyLabels) {
        label.draw(window);
    }
}

Player::Movement SettingScreen::getMovement(int id) {
    Player::Movement movement;
    switch (id) {
        case (int)Type::Up:
            movement = Player::Movement::Up;
            break;
        case (int)Type::Down:
            movement = Player::Movement::Down;
            break;
        case (int)Type::Left:
            movement = Player::Movement::Left;
            break;
        case (int)Type::Right:
            movement = Player::Movement::Right;
            break;
        default:
            movement = Player::Movement::Up;
    }
    return movement;
}
