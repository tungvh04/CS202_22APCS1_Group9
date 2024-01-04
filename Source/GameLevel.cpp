#include <GameLevel.hpp>

#include <Const.hpp>

GameLevel::GameLevel() {
    load();
}

void GameLevel::load() {
    std::ifstream file(Constants::savePath);
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        mScore = std::stoi(line);
        file.close();
    }
    else {
        mScore = 0;
    }
}

void GameLevel::save() {
    std::ofstream file(Constants::savePath);
    if (file.is_open()) {
        file << mScore;
        file.close();
    }
}

int GameLevel::getLevel() const {
    int level = mScore / 100;
    return level <= 1 ? 1 : level;
}


float GameLevel::getSpeedMultiplier() const {
    return (getLevel() - 1) * 0.2 + 1;
}

void GameLevel::restart() {
    mScore = 0;
}
void GameLevel::incrementScore(float score) {
    mScore += score;
}
void GameLevel::setScore(float score) {
    mScore = score;
}
float GameLevel::getScore() const {
    return mScore;
}

GameLevel gameLevel;