#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constant.h"
#include <map>
#include <iostream>

// singleton
class SoundHolder {
public:
    static SoundHolder& getInstance();
    ~SoundHolder();

public: 
    sf::SoundBuffer& getSoundBuffer(int id);

private:
    SoundHolder();

private:
    std::map<int, sf::SoundBuffer> soundHolder;

private: 
    void load(int key, std::string file);

private:
    std::string soundFolder = "resource/sound/";

    std::string startSound              = soundFolder + "Start.wav";
    std::string buttonMoveSound         = soundFolder + "Button Move.wav";
    std::string buttonEnterSound        = soundFolder + "Button Enter.wav";
    std::string carSound                = soundFolder + "Car.wav";
    std::string trainSound              = soundFolder + "Train.wav";
    std::string logSound                = soundFolder + "Log.wav";
    std::string hitSound                = soundFolder + "Hit.wav";
    std::string playerMoveSound         = soundFolder + "Player Move.wav";
    std::string riverJumpSound          = soundFolder + "River Jump.wav";
    std::string riverFlowSound          = soundFolder + "River Flow.wav";
};