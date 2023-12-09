#ifndef INDEXER_HPP
#define INDEXER_HPP

#include <map>

class Indexer{
private:
    sf::Vector2f origin;

    std::map<pair<int,int>,int> stateBoard;
public:
    void setOrigin(sf::Vector2f);

    void setState(int x,int y,int state);
}

#endif //INDEXER_HPP