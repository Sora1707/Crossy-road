#include "TextureHolder.h"


TextureHolder* TextureHolder::instance = nullptr;

TextureHolder* TextureHolder::getInstance() {
    if (!instance) {
        instance = new TextureHolder();
    }
    return instance;
}

void TextureHolder::load(int key, std::string file, sf::IntRect rect) {
    if (textureHolder.find(key) != textureHolder.end()) {
        std::cout << constant::ERROR << "Key Overlapping: value = " << key << "\n";
        exit(0);
    }
    
    sf::Texture texture;
    if (!texture.loadFromFile(file, rect)) {
        std::cout << constant::ERROR << "Failed loading file " << file << "\n";
        exit(0);
    }
        
    std::cout << constant::SUCCESS << "Key " << key << ": Loaded texture " << file << "\n";
    textureHolder[key] = texture;
}

sf::Texture* TextureHolder::getTexture(int key) {
    if (textureHolder.find(key) == textureHolder.end()) {
        std::cout << constant::ERROR << "Value " << key << " is not in the map\n";
        exit(0);
    }
    return &textureHolder[key];
}

TextureHolder::TextureHolder() {
    std::cout << constant::INFO << "Start loading textures...\n";

    using namespace Textures;

    // Player
    load((int)Player::Left01, playerLeftTexture01);
    load((int)Player::Right01, playerRightTexture01);
    load((int)Player::Up01, playerUpTexture01);
    load((int)Player::Down01, playerDownTexture01);

    load((int)Player::Left02, playerLeftTexture02);
    load((int)Player::Right02, playerRightTexture02);
    load((int)Player::Up02, playerUpTexture02);
    load((int)Player::Down02, playerDownTexture02);

    load((int)Player::Left03, playerLeftTexture03);
    load((int)Player::Right03, playerRightTexture03);
    load((int)Player::Up03, playerUpTexture03);
    load((int)Player::Down03, playerDownTexture03);

    load((int)Player::Left04, playerLeftTexture04);
    load((int)Player::Right04, playerRightTexture04);
    load((int)Player::Up04, playerUpTexture04);
    load((int)Player::Down04, playerDownTexture04);

    load((int)Player::Left05, playerLeftTexture05);
    load((int)Player::Right05, playerRightTexture05);
    load((int)Player::Up05, playerUpTexture05);
    load((int)Player::Down05, playerDownTexture05);

    // Grass
    load((int)Grass::Grass01, grass01Texture);
    load((int)Grass::Grass02, grass02Texture);
    load((int)Grass::Grass03, grass03Texture);
    load((int)Grass::Grass04, grass04Texture);
    load((int)Grass::Grass05, grass05Texture);
    load((int)Grass::Grass06, grass06Texture);

    // Obstacle
    load((int)Obstacle::Statue, statueTexture);
    load((int)Obstacle::SmallRock, smallRockTexture);
    load((int)Obstacle::BigRock, bigRockTexture);
    load((int)Obstacle::Tomb, tombTexture);
    load((int)Obstacle::BrokenTomb, brokenTombTexture);

    // River
    load((int)River::Default, riverTexture);
    load((int)River::WithGrass, riverWithGrassTexture);
    load((int)River::LilyPad, lilyPadTexture);

    // Road
    load((int)Road::Default, roadTexture);

    // Rail
    load((int)Rail::Default, railTexture);
    load((int)Rail::Traffic, trafficRailTexture);
    load((int)Rail::TrafficActive, trafficRailActiveTexture);

    // Car
    load((int)Car::Left01, carLeftTexture01);
    load((int)Car::Right01, carRightTexture01);
    load((int)Car::Left02, carLeftTexture02);
    load((int)Car::Right02, carRightTexture02);
    load((int)Car::Left03, carLeftTexture03);
    load((int)Car::Right03, carRightTexture03);
    load((int)Car::Left04, carLeftTexture04);
    load((int)Car::Right04, carRightTexture04);
    load((int)Car::Left05, carLeftTexture05);
    load((int)Car::Right05, carRightTexture05);

    // Train
    load((int)Train::Left, trainLeftTexture);
    load((int)Train::Right, trainRightTexture);

    // Wood
    load((int)Mountable::Wood, woodTexture);

    // Background
    load((int)Background::Main, mainBackground);

    // Component Button
    load((int)Button::Normal, buttonTexture, sf::IntRect(0, 0, 200, 50));
    load((int)Button::Active, buttonTexture, sf::IntRect(0, 50, 200, 50));
    load((int)Button::Hovered, buttonTexture, sf::IntRect(0, 100, 200, 50));


    std::cout << constant::INFO << "Finished loading textures...\n";
}

TextureHolder::~TextureHolder() {
    std::cout << constant::INFO << "Deleted Texture Holder...\n";
    delete instance;
}
