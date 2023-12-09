#ifndef WORLD_BUILDER_HPP
#define WORLD_BUILDER_HPP

#include <Entity.hpp>
#include <Const.hpp>
#include <Utility.hpp>
#include <CollisionBox.hpp>
#include <TileSystem.hpp>
#include <Car.hpp>
#include <Indexer.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <fstream>

class WorldBuilder {
private:
    TileBuilderRow* tileManager;
    CarFactoryManager* carMaker;
    Indexer* controlManager;
public:
    WorldBuilder();


};

#endif //WORLD_BUILDER_HPP