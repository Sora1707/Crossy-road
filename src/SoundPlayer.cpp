#include "SoundPlayer.h"

void SoundPlayer::setVolume(float volume) {
    this->volume = volume;
}

float SoundPlayer::getVolume() {
    return volume;
}

void SoundPlayer::addSong(int id, float volume) {
    SoundHolder& soundHolder = SoundHolder::getInstance();
    sf::Sound sound;
    sound.setBuffer(soundHolder.getSoundBuffer(id));
    sound.setVolume(volume);
    soundPlayer.push_back(sound);
    soundPlayer.back().play();
}

void SoundPlayer::handlePlayer() {
    for (auto it = soundPlayer.begin(); it < soundPlayer.end(); ++it) {
        if (it->getStatus() == sf::SoundSource::Status::Stopped) {
            soundPlayer.erase(it);
        }
    }
}
