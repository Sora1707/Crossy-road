#include "Constant.h"
#include <iostream>
#include "Util/Logger.h"

namespace constant {
    sf::Font fontArial;

    void loadFont() {
        if (!fontArial.loadFromFile("resource/fonts/arial.ttf")) {
            logger::error << "Can't load the font !!!";
            exit(0);
        }
        logger::success << "Loaded font Arial at resource/fonts/arial.ttf\n";
    }
} // namespace constant