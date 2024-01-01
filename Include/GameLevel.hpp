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
    void setLevel(int level);
    float getSpeedMultiplier() const;
    void nextLevel();
    void restart();
private:
    int mLevel;
};

extern GameLevel gameLevel;

#endif // GAMELEVEL_HPP