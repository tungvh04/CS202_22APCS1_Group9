#ifndef GAMELEVEL_HPP
#define GAMELEVEL_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <MapState.hpp>

class GameLevel {
public:
    GameLevel();
    // ~GameLevel();

    void saveHighScore(TypeMap::ID typeMap);

    void load();
    void save();
    int getLevel() const;
    float getSpeedMultiplier() const;
    void restart();
    void incrementScore(float score);
    void setScore(float score);
    float getScore() const;

    static std::vector<float> loadHighScore(TypeMap::ID typeMap);
private:
    float mScore;
};

extern GameLevel gameLevel;

#endif // GAMELEVEL_HPP