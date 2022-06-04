#include "GameTextures.h"

GameTextures::GameTextures() {
    std::filesystem::path spritesDirPath = "../Assets/Sprites";

    if (!this->FirstPlayerIdle.loadFromFile(spritesDirPath / "tank-green.png")){
        throw std::exception();
    }
    if (!this->SecondPlayerIdle.loadFromFile(spritesDirPath / "tank-red.png")){
        throw std::exception();
    }
    if (!this->ThirdPlayerIdle.loadFromFile(spritesDirPath / "tank-blue.png")){
        throw std::exception();
    }
    if (!this->Bullet.loadFromFile(spritesDirPath / "bullet.png")){
        throw std::exception();
    }
    if (!this->VerticalBorder.loadFromFile(spritesDirPath / "verticalBorder.png")){
        throw std::exception();
    }
    if (!this->HorizontalBorder.loadFromFile(spritesDirPath / "horizontalBorder.png")){
        throw std::exception();
    }
    if (!this->Box.loadFromFile(spritesDirPath / "grass-plate.png")){
        throw std::exception();
    }
    if (!this->MenuBackground.loadFromFile(spritesDirPath / "start-menu-background.png")){
        throw std::exception();
    }
}

sf::Texture& GameTextures::getPlayerTextureById(int id) {
    if (id == 0) {
        return this->FirstPlayerIdle;
    }
    if (id == 1) {
        return this->SecondPlayerIdle;
    }
    return this->ThirdPlayerIdle;
}
