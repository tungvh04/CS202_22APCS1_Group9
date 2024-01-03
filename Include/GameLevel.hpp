#ifndef GAMELEVEL_HPP
#define GAMELEVEL_HPP

#include <fstream>
#include <iostream>
#include <string>

class GameLevel {
public:
    GameLevel();
    // ~GameLevel();

    void load();
    void save();
    int getLevel() const;
    float getSpeedMultiplier() const;
    void restart();
    void incrementScore(float score);
    void setScore(float score);
    float getScore() const;
private:
    float mScore;
};

extern GameLevel gameLevel;

#endif // GAMELEVEL_HPP