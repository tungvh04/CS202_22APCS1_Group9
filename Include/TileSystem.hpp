#ifndef TILESYSTEM_HPP
#define TILESYSTEM_HPP

#include <Entity.hpp>
#include <Const.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <fstream>

class Tile{
private:
    sf::Vector2f pos;

    sf::Texture* tTexture;
    //int tTextureID;

    sf::Sprite tObj;

public:
    Tile();
    ~Tile();

    void draw(sf::RenderWindow& window);
    void setPos(sf::Vector2f _pos);
    void setTexture(sf::Texture* _texture);
    sf::Vector2f getPos();
};

class TileSystem{
private:
    std::vector<sf::Texture> tTexture;
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
};

class TileBuilderRow: public TileSystem{
private:
    sf::Vector2f spawnOrigin;

    int widthRadius,heightRadius;
    int replaceAmount;

    int rowCnt;

    float shiftAmount;

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
};

#endif //TILESYSTEM_HPP