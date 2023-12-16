#include <Indexer.hpp>

void Indexer::setOrigin(sf::Vector2f _point) {
    origin=_point;
}

void Indexer::setState(sf::Vector2i p,int state) {
    stateBoard[{p.x,p.y}]=state;
}

sf::Vector2i Indexer::getIndex(sf::Vector2f _point) {
    sf::Vector2f kq=origin-_point;
    //std::cout<<"!"<<kq.x/Constants::GridSize<<' '<<kq.y/Constants::GridSize<<' ';
    if (kq.x>=origin.x) kq.x+=Constants::GridSize/2.0;
    else kq.x-=Constants::GridSize/2.0;
    if (kq.y<=origin.y) kq.y+=Constants::GridSize/2.0;
    else kq.y-=Constants::GridSize/2.0;
    //std::cout<<"!"<<kq.x/Constants::GridSize<<' '<<kq.y/Constants::GridSize<<'\n';
    kq.x=-kq.x;
    //std::cout<<kq.x/Constants::GridSize<<' '<<kq.y/Constants::GridSize<<'\n';
    return sf::Vector2i(kq/Constants::GridSize);
}

int Indexer::getState(sf::Vector2i p) {
    return stateBoard[{p.x,p.y}];
}

float Indexer::getX(int p) {
    return origin.x+p*Constants::GridSize;
}

float Indexer::getY(int p) {
    return origin.y+p*Constants::GridSize;
}

sf::Vector2f Indexer::getCoord(int x,int y) {
    return sf::Vector2f(origin.x+x*Constants::GridSize,origin.y+y*Constants::GridSize);
}

void Indexer::setGen(int p) {
    stateRow[p]=true;
}

bool Indexer::isGen(int p) {
    return stateRow[p];
}