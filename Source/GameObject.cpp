#include <iostream>

#include <GameObject.hpp>

const std::vector<std::vector<Tile::Type>> RowObject::initilizeTileTypes() {
    std::vector<Tile::Type> grass = {Tile::Grass};
    std::vector<Tile::Type> sand = {Tile::Sand};
    std::vector<Tile::Type> ice = {Tile::Ice};
    std::vector<Tile::Type> road = {Tile::Road};
    std::vector<Tile::Type> rail = {Tile::Rail};
    std::vector<Tile::Type> grass2 = {Tile::Grass};
    std::vector<Tile::Type> sand2 = {Tile::Sand};
    std::vector<Tile::Type> sand3 = {Tile::Sand};
    std::vector<Tile::Type> grass3 = {Tile::Grass};
    std::vector<Tile::Type> grass4 = {Tile::Grass};
    std::vector<Tile::Type> road2 = {Tile::Road};
    std::vector<Tile::Type> rail2 = {Tile::Rail};
    std::vector<Tile::Type> grass5 = {Tile::Grass};
    std::vector<Tile::Type> grass6 = {Tile::Grass};
    std::vector<Tile::Type> grass7 = {Tile::Grass};
    std::vector<Tile::Type> log = {Tile::Log};
    std::vector<Tile::Type> soil = {Tile::Soil};
    std::vector<std::vector<Tile::Type>> tileTypes = {grass, sand, ice, road, rail, grass2, sand2, sand3, grass3, grass4, road2, rail2, grass5, grass6, grass7, log, soil};
    return tileTypes;
}

const std::vector<std::vector<Obstacle::Type>> RowObject::initilizeObstacleTypes() {
    std::vector<Obstacle::Type> road = {Obstacle::Car, Obstacle::Car1, Obstacle::Oto, Obstacle::Oto_1, Obstacle::Oto1, Obstacle::Oto1_1, Obstacle::Oto2, Obstacle::Oto2_1};
    std::vector<Obstacle::Type> rail = {Obstacle::Train, Obstacle::Train1};
    std::vector<Obstacle::Type> sand = {Obstacle::Animal3};
    std::vector<Obstacle::Type> grass = {Obstacle::Tree, Obstacle::Tree1, Obstacle::Tree2, Obstacle::Tree3, Obstacle::Tree4, Obstacle::Tree5};
    std::vector<Obstacle::Type> ice = {Obstacle::Island};
    std::vector<Obstacle::Type> grass2 = {Obstacle::Stone};
    std::vector<Obstacle::Type> sand2 = {};
    std::vector<Obstacle::Type> sand3 = {};
    std::vector<Obstacle::Type> grass3 = {Obstacle::Animal1, Obstacle::Animal2};
    std::vector<Obstacle::Type> grass4 = {};
    std::vector<Obstacle::Type> road2 = {Obstacle::Car, Obstacle::Car1, Obstacle::Oto, Obstacle::Oto_1, Obstacle::Oto1, Obstacle::Oto1_1, Obstacle::Oto2, Obstacle::Oto2_1};
    std::vector<Obstacle::Type> rail2 = {Obstacle::Train, Obstacle::Train1};
    std::vector<Obstacle::Type> grass5 = {Obstacle::SlowDown};
    std::vector<Obstacle::Type> grass6 = {Obstacle::SpeedUp};
    std::vector<Obstacle::Type> grass7 = {Obstacle::IceCream};
    std::vector<Obstacle::Type> log = {Obstacle::Island};
    std::vector<Obstacle::Type> soil = {Obstacle::Animal4};
    std::vector<std::vector<Obstacle::Type>> obstacleTypes = {grass, sand, ice, road, rail, grass2, sand2, sand3, grass3, grass4, road2, rail2, grass5, grass6, grass7, log, soil};
    return obstacleTypes;
}

const static std::vector<std::vector<Tile::Type>> mTileTypes = RowObject::initilizeTileTypes();
const static std::vector<std::vector<Obstacle::Type>> mObstacleTypes = RowObject::initilizeObstacleTypes();


GameObject::GameObject(sf::Vector2f spawnOrigin, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures, std::map<Animations::ID, Animation>& animations) : getBattlefieldBounds(getBattlefieldBounds), mTextures(textures), mSpawnOrigin(spawnOrigin), mAnimations(animations) {
    SceneNode::Ptr tileRow(new SceneNode);
    mTiles = tileRow.get();
    attachChild(std::move(tileRow));
    SceneNode::Ptr obstacleRow(new SceneNode);
    mObstacles = obstacleRow.get();
    attachChild(std::move(obstacleRow));
    initialGenerate();
}

void GameObject::initialGenerate() {
    for (int i = 0; i < Constants::initialShift;i++) {
        int rowType = rand() % RowObject::TypeCount;
        SceneNode::Ptr tileRow(new TileRow(mTileTypes[rowType], getBattlefieldBounds, mTextures));
        SceneNode::Ptr obstacleRow(new ObstacleRow(mObstacleTypes[rowType], getBattlefieldBounds, mTextures, mAnimations));
        tileRow.get()->setPosition(mSpawnOrigin);
        obstacleRow.get()->setPosition(mSpawnOrigin);
        mTiles->attachChild(std::move(tileRow));
        mObstacles->attachChild(std::move(obstacleRow));
        mSpawnOrigin.y -= Constants::GridSize;
    }
    for (int i = Constants::initialShift; i <= Constants::initialShift; i++) {
        SceneNode::Ptr tileRow(new TileRow(mTileTypes[RowObject::Grass], getBattlefieldBounds, mTextures));
        tileRow.get()->setPosition(mSpawnOrigin);
        mTiles->attachChild(std::move(tileRow));
        mSpawnOrigin.y -= Constants::GridSize;
    }
}

void GameObject::setSpawnOrigin(sf::Vector2f spawnOrigin) {
    mSpawnOrigin = spawnOrigin;
}

void GameObject::updateCurrent(sf::Time dt) {
    sf::FloatRect battlefieldBounds = getBattlefieldBounds();
    while (mSpawnOrigin.y > battlefieldBounds.top) {
        int rowType = rand() % RowObject::TypeCount;
        while (rowType==last) {
            rowType = rand() % RowObject::TypeCount;
        }
        last=rowType;
        SceneNode::Ptr tileRow(new TileRow(mTileTypes[rowType], getBattlefieldBounds, mTextures));
        SceneNode::Ptr obstacleRow(new ObstacleRow(mObstacleTypes[rowType], getBattlefieldBounds, mTextures, mAnimations));
        tileRow.get()->setPosition(mSpawnOrigin);
        obstacleRow.get()->setPosition(mSpawnOrigin);
        mTiles->attachChild(std::move(tileRow));
        mObstacles->attachChild(std::move(obstacleRow));
        mSpawnOrigin.y -= Constants::GridSize;
    }
    removeWrecks();
}