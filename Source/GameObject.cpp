#include <iostream>

#include <GameObject.hpp>

const std::vector<std::vector<Tile::Type>> RowObject::initilizeTileTypes() {
    std::vector<Tile::Type> grass = {Tile::Grass};
    std::vector<Tile::Type> road = {Tile::Sand};
    std::vector<Tile::Type> ice = {Tile::Ice};
    std::vector<std::vector<Tile::Type>> tileTypes = {grass, road, ice};
    // return {grass, road, ice};
    return tileTypes;
}

const std::vector<std::vector<Obstacle::Type>> RowObject::initilizeObstacleTypes() {
    std::vector<Obstacle::Type> road = {Obstacle::Car, Obstacle::Car1};
    std::vector<Obstacle::Type> none = {};
    std::vector<std::vector<Obstacle::Type>> obstacleTypes = {none, road, none};
    // return {none, road, none};
    return obstacleTypes;
}

const static std::vector<std::vector<Tile::Type>> mTileTypes = RowObject::initilizeTileTypes();
const static std::vector<std::vector<Obstacle::Type>> mObstacleTypes = RowObject::initilizeObstacleTypes();


GameObject::GameObject(sf::Vector2f spawnOrigin, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures) : getBattlefieldBounds(getBattlefieldBounds), mTextures(textures), mSpawnOrigin(spawnOrigin) {
    SceneNode::Ptr tileRow(new SceneNode);
    mTiles = tileRow.get();
    attachChild(std::move(tileRow));
    SceneNode::Ptr obstacleRow(new SceneNode);
    mObstacles = obstacleRow.get();
    attachChild(std::move(obstacleRow));
}

void GameObject::setSpawnOrigin(sf::Vector2f spawnOrigin) {
    mSpawnOrigin = spawnOrigin;
}

void GameObject::updateCurrent(sf::Time dt) {
    sf::FloatRect battlefieldBounds = getBattlefieldBounds();
    while (mSpawnOrigin.y > battlefieldBounds.top) {
        int rowType = rand() % RowObject::TypeCount;
        SceneNode::Ptr tileRow(new TileRow(mTileTypes[rowType], getBattlefieldBounds, mTextures));
        // SceneNode::Ptr obstacleRow(new ObstacleRow(sf::Vector2f(200, 0), mObstacleTypes[rowType], getBattlefieldBounds, mTextures));
        SceneNode::Ptr obstacleRow(new ObstacleRow(mObstacleTypes[rowType], getBattlefieldBounds, mTextures));
        tileRow.get()->setPosition(mSpawnOrigin);
        obstacleRow.get()->setPosition(mSpawnOrigin);
        mTiles->attachChild(std::move(tileRow));
        mObstacles->attachChild(std::move(obstacleRow));
        mSpawnOrigin.y -= Constants::GridSize;
    }
    removeWrecks();
}