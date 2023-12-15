#ifndef INDEXER_HPP
#define INDEXER_HPP

#include <Entity.hpp>
#include <Const.hpp>
#include <Utility.hpp>

#include <iostream>
#include <fstream>
#include <map>

class Indexer{
private:
    sf::Vector2f origin;

    std::map<std::pair<int,int>,int> stateBoard;
public:
    void setOrigin(sf::Vector2f);

    void setState(sf::Vector2i p,int state);

    sf::Vector2i getIndex(sf::Vector2f);
    int getState(sf::Vector2i);
};

#endif //INDEXER_HPP