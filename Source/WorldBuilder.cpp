#include <WorldBuilder.hpp>

void WorldBuilder::setBuilder(TileBuilderRow* target) {
    tileManager=target;
}

void WorldBuilder::setFactory(CarFactoryManager* target) {
    tileManager=target;
}

void WorldBuilder::setIndexer(Indexer* target) {
    tileManager=target;
}

void WorldBuilder::buildFrontRow() {
    
}