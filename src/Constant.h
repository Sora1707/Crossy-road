#pragma once
#include <SFML/Graphics.hpp>

// namespace constant (GLOBAL)
namespace constant {
    // Font
    extern sf::Font fontArial;
    void loadFont();

    // Color
    sf::Color const BACKGROUND_COLOR = sf::Color(255, 255, 153);
    sf::Color const YELLOW           = sf::Color::Yellow;
    sf::Color const BLACK            = sf::Color::Black;
    sf::Color const WHITE            = sf::Color::White;

    // APP 
    const float APP_VELOCITY    = 0.5;
    const float APP_SPEEDUP_VELOCITY = 5;
    const int APP_FPS           = 60;
    const int APP_WIDTH         = 1600;
    const int APP_HEIGHT        = 900;
    const std::string APP_TITLE = "Crossy Road";
    const int TILE_SIZE         = 100;
    const int APP_ROW           = 9;
    const int APP_COLUMN        = 16;
    const int APP_SAFE_LANE     = 4;

    // PLAYER: scale: 32/48
    // NEW PLAYER: scale 1/1
    const int PLAYER_WIDTH      = 75;
    const int PLAYER_HEIGHT     = 75;
    const int PLAYER_START_X      = 7;
    const int PLAYER_START_Y      = 5;
    const int PLAYER_SPRITES      = 5;

    // CAR
    const float CAR_WIDTH  = 192;
    const float CAR_HEIGHT = TILE_SIZE; // real is 80

    // TRAIN
    const float TRAIN_WIDTH = 858;
    const float TRAIN_HEIGHT = TILE_SIZE; // real is 80

    // WOOD
    const float WOOD_WIDTH = 200;
    const float WOOD_HEIGHT = TILE_SIZE; // real is 70

    // TEXT
    const std::string ERROR = "[ERROR] ";
    const std::string WARN = "[WARNING] ";
    const std::string SUCCESS = "[SUCCESS] ";
    const std::string INFO = "[INFO] ";

    // BUTTON
    const float BUTTON_WIDTH = 200;
    const float BUTTON_HEIGHT = 50;

    // CHARACTER BUTTON
    const float CHARACTER_BUTTON_WIDTH  = 200;
    const float CHARACTER_BUTTON_HEIGHT = 200;

    // Color
} // namespace constant

namespace constant {
    enum class Direction {
        Left,
        Right,
        Up,
        Down
    };

    enum class Screen {
        Menu,
        Setting,
        Game,
        Count
    };
}

namespace constant {
    const std::string SAVED_FOLDER       = "data/";
    const std::string SAVED_SETTING_FILE = SAVED_FOLDER + "setting.txt";
    const std::string SAVED_PLAYER_FILE  = SAVED_FOLDER + "player.txt";
    const std::string SAVED_TILES_FILE   = SAVED_FOLDER + "tiles.txt";
}

namespace Textures {
    enum class Player {
        StartIndex = 1000,
        Left01 = 1000,
        Right01,
        Up01,
        Down01,
        Left02,
        Right02,
        Up02,
        Down02,
        Left03,
        Right03,
        Up03,
        Down03,
        Left04,
        Right04,
        Up04,
        Down04,
        Left05,
        Right05,
        Up05,
        Down05,
        Texture01 = Left01,
        Texture02 = Left02,
        Texture03 = Left03,
        Texture04 = Left04,
        Texture05 = Left05,
    };

    enum class Grass {
        StartIndex = 10,
        Grass01 = 10,
        Grass02,
        Grass03,
        Grass04, 
        Grass05,
        Grass06,
        Count = 6
    };

    enum class Obstacle {
        StartIndex = 20,
        Statue = 20,
        SmallRock,
        BigRock,
        Tomb,
        BrokenTomb,
        Count = 5,
    };

    enum class River {
        StartIndex = 30,
        Default = 30,
        WithGrass,
        LilyPad,
        Count = 2,
    };

    enum class Road {
        StartIndex = 40,
        Default = 40,
        Count = 1,
    };

    enum class Rail {
        StartIndex = 50,
        Default = 50,
        Traffic,
        TrafficActive,
        Count = 3,
    };

    enum class Car {
        Count = 5,
        Left01 = 100,
        Left02,
        Left03,
        Left04,
        Left05,
        Right01,
        Right02,
        Right03,
        Right04,
        Right05,
    };

    enum class Train {
        Left = 110,
        Right,
    };

    enum class Mountable {
        Wood = 200,
    };

    enum class Background {
        Main = 500,
    };

    enum class Button {
        Normal = 600,
        Active,
        Hovered
    };
}

namespace Sound {
    enum Sound {
        Start,
        ButtonMove,
        ButtonEnter,
        Car,
        Train,
        Log,
        Hit,
        PlayerMove,
        RiverJump,
        RiverFlow,
    };
}