#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include "SoundHolder.h"

class SoundPlayer {
private:
    float volume = 100;
    std::vector<sf::Sound> soundPlayer;

public:
    void setVolume(float volume);
    float getVolume();

    void addSong(int id, float volume = 100);

public:
    void handlePlayer();
};