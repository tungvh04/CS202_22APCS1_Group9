#ifndef TILESYSTEM_HPP
#define TILESYSTEM_HPP

#include <Entity.hpp>
#include <Const.hpp>
#include <Utility.hpp>
#include <CollisionBox.hpp>
#include <Object.hpp>
#include <Indexer.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <fstream>

class Tile: public Object,BoundingBox{
private:

public:
    Tile();
    ~Tile();
};

class TileState {
private:
    bool _isRoad;
public:
    void setRoad(int x);
    
    bool isRoad();
};

class TileSystem{
private:
    std::vector<sf::Texture> tTexture;
    std::vector<TileState> tState;
    std::deque<Tile*> tileContainer;

public:
    TileSystem();
    ~TileSystem();

    void load();
    void init();

    void addTile(sf::Vector2f _pos,int textureID);
    void addTile(Tile* _tile);
    void draw(sf::RenderWindow& window);
    void push_back(Tile* _tile);
    void pop_front();
    int getSize();
    int getIDSize();

    bool isRoad(int id);
};

class TileBuilderRow: public TileSystem{
private:
    sf::Vector2f spawnOrigin;

    int widthRadius,heightRadius;
    int replaceAmount;

    int rowCnt;

    float shiftAmount;

    Indexer* controller=nullptr;

public: 
    TileBuilderRow();

    void init();
    void buildFrontRow();
    void buildFrontRow(int ID);
    //void deleteFrontrow();
    //void buildBackRow();
    void deleteBackRow();
    void buildTillFull();
    void shiftX(int step);
    void shiftY(int step);
    void setOrigin(sf::Vector2f _pos);
    void setCentre(sf::Vector2f _pos);
    void update(sf::Vector2f playerPos);
    void setController(Indexer* tmp);
};

#endif //TILESYSTEM_HPP