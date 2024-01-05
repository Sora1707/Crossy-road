#include "Screen.h"

Screen::Screen() {
}

Screen::~Screen() {
}

void Screen::setCurrentScreenId(int id) {
    currentScreenId = id;
}

int Screen::getCurrentScreenId() {
    return currentScreenId;
}

void Screen::setPrevScreenId(int id) {
    prevScreenId = id;
}

int Screen::getPrevScreenId() {
    return prevScreenId;
}

void Screen::setIsExit(bool state) {
    isExit = state;
}

bool Screen::getIsExit() {
    return isExit;
}

void Screen::setSoundPlayer(SoundPlayer* soundPlayer) {
    this->soundPlayer = soundPlayer;
}
