#include <GameLevel.hpp>

#include <Const.hpp>

GameLevel::GameLevel() {
    load();
}

void GameLevel::nextLevel() {
    mLevel++;
}

void GameLevel::load() {
    std::ifstream file(Constants::savePath);
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        mLevel = std::stoi(line);
        file.close();
    }
    else {
        mLevel = 1;
    }
}

void GameLevel::save() {
    std::ofstream file(Constants::savePath);
    if (file.is_open()) {
        file << mLevel;
        file.close();
    }
}

int GameLevel::getLevel() const {
    return mLevel;
}

void GameLevel::setLevel(int level) {
    mLevel = level;
}

float GameLevel::getSpeedMultiplier() const {
    return (mLevel - 1) * 0.2 + 1;
}

void GameLevel::restart() {
    mLevel = 1;
}

GameLevel gameLevel;