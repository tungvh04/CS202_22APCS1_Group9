#include <GameLevel.hpp>

#include <Const.hpp>

GameLevel::GameLevel() {
    load();
}

void GameLevel::saveHighScore(TypeMap::ID typeMap) {
    std::vector<float> highScore = loadHighScore(typeMap);
    if (highScore.size() < Constants::MaxNumSaveScore) {
        highScore.push_back(mScore);
    }
    else {
        if (highScore.back() < mScore) {
            highScore.back() = mScore;
        }
    }
    sort(highScore.begin(), highScore.end(), std::greater<float>());

    std::ofstream file;
    file.open(Constants::saveMapPath + "map" + std::to_string(typeMap) + ".txt");
    if (file.is_open()) {
        for (auto score : highScore) {
            file << score << std::endl;
        }
        file.close();
    }
}

std::vector<float> GameLevel::loadHighScore(TypeMap::ID typeMap) {
    std::ifstream file;
    file.open(Constants::saveMapPath + "map" + std::to_string(typeMap) + ".txt");
    if (!file.is_open()) {
        return std::vector<float> (Constants::MaxNumSaveScore, 0);
    }
    float score;
    std::vector<float> highScore;
    while (file >> score) {
        // highScore.push_back(score);
        if (highScore.size() < Constants::MaxNumSaveScore) {
            highScore.push_back(score);
        }
    }
    file.close();
    while (highScore.size() < Constants::MaxNumSaveScore) {
        highScore.push_back(0);
    }
    return highScore;
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