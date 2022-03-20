#include <filesystem>
#include "GameTextures.h"

GameTextures::GameTextures() {
    std::filesystem::path spritesDirPath = "../Assets/Sprites";

    if (!this->FirstPlayerIdle.loadFromFile(spritesDirPath / "tank-green.png")){
        throw std::exception();
    }
    if (!this->SecondPlayerIdle.loadFromFile(spritesDirPath / "tank-red.png")){
        throw std::exception();
    }
    if (!this->VerticalBorder.loadFromFile(spritesDirPath / "vertical-border.png")){
        throw std::exception();
    }
    if (!this->HorizontalBorder.loadFromFile(spritesDirPath / "horizontal-border.png")){
        throw std::exception();
    }
    if (!this->Box.loadFromFile(spritesDirPath / "grass-plate.png")){
        throw std::exception();
    }
    if (!this->MenuBackground.loadFromFile(spritesDirPath / "start-menu-background.png")){
        throw std::exception();
    }
}