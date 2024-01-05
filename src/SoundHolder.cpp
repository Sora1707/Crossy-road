#include "SoundHolder.h"

SoundHolder& SoundHolder::getInstance() {
    static SoundHolder instance;
    return instance;
}

SoundHolder::~SoundHolder() {
}

sf::SoundBuffer& SoundHolder::getSoundBuffer(int id) {
    if (soundHolder.find(id) == soundHolder.end()) {
        std::cout << constant::ERROR << "Sound with id = " << id << "does not exist\n";
        exit(0);
    }
    return soundHolder[id];
}


SoundHolder::SoundHolder() {
    std::cout << constant::INFO << "Start loading sound...\n";

    load((int)Sound::Start, startSound);
    load((int)Sound::ButtonMove, buttonMoveSound);
    load((int)Sound::ButtonEnter, buttonEnterSound);
    load((int)Sound::Car, carSound);
    load((int)Sound::Train, trainSound);
    load((int)Sound::Log, logSound);
    load((int)Sound::Hit, hitSound);
    load((int)Sound::PlayerMove, playerMoveSound);
    load((int)Sound::RiverJump, riverJumpSound);
    load((int)Sound::RiverFlow, riverFlowSound);

    std::cout << constant::INFO << "Finished loading sound...\n";
}


void SoundHolder::load(int key, std::string file) {
    if (soundHolder.find(key) != soundHolder.end()) {
        std::cout << constant::ERROR << "Key Overlapping: value = " << key << "\n";
        exit(0);
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(file)) {
        std::cout << constant::ERROR << "Failed loading file " << file << "\n";
        exit(0);
    }

    std::cout << constant::SUCCESS << "Key " << key << ": Loaded sound " << file << "\n";
    soundHolder[key] = buffer;
}
