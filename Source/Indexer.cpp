#include <Indexer.hpp>

void Indexer::setOrigin(sf::Vector2f _point) {
    origin=_point;
}

void Indexer::setState(sf::Vector2i p,int state) {
    stateBoard[{p.x,p.y}]=state;
}

sf::Vector2i Indexer::getIndex(sf::Vector2f _point) {
    sf::Vector2f kq=origin-_point;
    if (kq.x<0) kq.x+=Constants::GridSize/2.0;
    else kq.x-=Constants::GridSize/2.0;
    if (kq.y<0) kq.y+=Constants::GridSize/2.0;
    else kq.y-=Constants::GridSize/2.0;
    return sf::Vector2i(kq/Constants::GridSize);
}

int Indexer::getState(sf::Vector2i p) {
    return stateBoard[{p.x,p.y}];
}