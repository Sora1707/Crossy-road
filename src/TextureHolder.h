#pragma once
#include <SFML/Graphics.hpp>
#include "Constant.h"
#include <map>
#include <iostream>

// singleton
class TextureHolder {
public:
    static TextureHolder* getInstance();
    ~TextureHolder();

public: 
    sf::Texture* getTexture(int key);
	
private:
    TextureHolder();
    static TextureHolder* instance;

private: 
    std::map<int, sf::Texture> textureHolder;

private:
    void load(int key, std::string file, sf::IntRect rect = sf::IntRect());

private: 
    const std::string imagesFolder = "resource/images/";

    /* PLAYER */
    const std::string playerFolder       = imagesFolder + "players/";
    const std::string playerLeftTexture01 = playerFolder + "Left01.png";
    const std::string playerRightTexture01 = playerFolder + "Right01.png";
    const std::string playerUpTexture01    = playerFolder + "Up01.png";
    const std::string playerDownTexture01  = playerFolder + "Down01.png";

    const std::string playerLeftTexture02  = playerFolder + "Left02.png";
    const std::string playerRightTexture02 = playerFolder + "Right02.png";
    const std::string playerUpTexture02    = playerFolder + "Up02.png";
    const std::string playerDownTexture02  = playerFolder + "Down02.png";

    const std::string playerLeftTexture03  = playerFolder + "Left03.png";
    const std::string playerRightTexture03 = playerFolder + "Right03.png";
    const std::string playerUpTexture03    = playerFolder + "Up03.png";
    const std::string playerDownTexture03  = playerFolder + "Down03.png";

    const std::string playerLeftTexture04  = playerFolder + "Left04.png";
    const std::string playerRightTexture04 = playerFolder + "Right04.png";
    const std::string playerUpTexture04    = playerFolder + "Up04.png";
    const std::string playerDownTexture04  = playerFolder + "Down04.png";

    const std::string playerLeftTexture05  = playerFolder + "Left05.png";
    const std::string playerRightTexture05 = playerFolder + "Right05.png";
    const std::string playerUpTexture05    = playerFolder + "Up05.png";
    const std::string playerDownTexture05  = playerFolder + "Down05.png";

    /* TILES */
    const std::string tilesFolder = imagesFolder + "tiles/";

    // Grass
    const std::string grassFolder = tilesFolder + "grass/";
    const std::string grass01Texture = grassFolder + "01.png";
    const std::string grass02Texture = grassFolder + "02.png";
    const std::string grass03Texture = grassFolder + "03.png";
    const std::string grass04Texture = grassFolder + "05.png";
    const std::string grass05Texture = grassFolder + "05.png";
    const std::string grass06Texture = grassFolder + "06.png";

    // Obstacle
    const std::string obstacleFolder = tilesFolder + "obstacle/";
    const std::string statueTexture  = obstacleFolder + "statue.png";
    const std::string smallRockTexture  = obstacleFolder + "smallRock.png";
    const std::string bigRockTexture  = obstacleFolder + "bigRock.png";
    const std::string tombTexture  = obstacleFolder + "tomb.png";
    const std::string brokenTombTexture  = obstacleFolder + "brokenTomb.png";

    // River
    const std::string riverFolder = tilesFolder + "river/";
    const std::string riverTexture = riverFolder + "River.png";
    const std::string riverWithGrassTexture = riverFolder + "RiverWithGrass.png";
    const std::string lilyPadTexture        = riverFolder + "LilyPad.png";

    // Road
    const std::string roadFolder  = tilesFolder + "road/";
    const std::string roadTexture = roadFolder + "Road.png";

    // Rail
    const std::string railFolder  = tilesFolder + "rail/";
    const std::string railTexture = railFolder + "Rail.png";
    const std::string trafficRailTexture = railFolder + "TrafficRail.png";
    const std::string trafficRailActiveTexture = railFolder + "TrafficRailActive.png";
    
    /* VEHICLES */
    const std::string vehiclesFolder = imagesFolder + "vehicles/";

    // Car
    const std::string carFolder = vehiclesFolder + "cars/";
    const std::string carLeftTexture01 = carFolder + "Left01.png";
    const std::string carRightTexture01 = carFolder + "Right01.png";
    const std::string carLeftTexture02  = carFolder + "Left02.png";
    const std::string carRightTexture02 = carFolder + "Right02.png";
    const std::string carLeftTexture03  = carFolder + "Left03.png";
    const std::string carRightTexture03 = carFolder + "Right03.png";
    const std::string carLeftTexture04  = carFolder + "Left04.png";
    const std::string carRightTexture04 = carFolder + "Right04.png";
    const std::string carLeftTexture05  = carFolder + "Left05.png";
    const std::string carRightTexture05 = carFolder + "Right05.png";

    // Train
    const std::string trainFolder       = vehiclesFolder + "trains/";
    const std::string trainLeftTexture = trainFolder + "Left.png";
    const std::string trainRightTexture = trainFolder + "Right.png";

    /* MOUNTABLE */
    const std::string mountablesFolder = imagesFolder + "mountables/";

    // Wood
    const std::string woodTexture  = mountablesFolder + "Wood.png";

    /* BACKGROUND */
    const std::string backgroundFolder = imagesFolder + "Background/";
    const std::string mainBackground   = backgroundFolder + "Main.png";

    /* COMPONENT */
    const std::string componentsFolder = imagesFolder + "Components/";
    const std::string buttonTexture    = componentsFolder + "Button.png";
};