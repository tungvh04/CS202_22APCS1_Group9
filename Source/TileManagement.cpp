#include <iostream>


#include <TileManagement.hpp>

Textures::ID toTextureID(Tile::Type type) {
    switch (type) {
        case Tile::Grass:
            return Textures::Grass;
        case Tile::Sand:
            return Textures::Sand;
        case Tile::Ice:
            return Textures::Ice;
        default:
            throw std::runtime_error("Invalid tile type");
    }
}
unsigned int Tile::getCategory() const {
    switch (mType) {
        case Grass:
            return Category::Grass | Category::Tile;
        case Sand:
            return Category::Sand | Category::Tile;
        case Ice:
            return Category::Ice | Category::Tile;
        default:
            throw std::runtime_error("Invalid tile type");
    }
}
void Tile::destroy() {
    isDestroy = true;
}
bool Tile::isDestroyed() const {
    return isDestroy;
}
Tile::Tile(Type type, const TextureHolder& textures) : mType(type), MovingObject(textures.get(toTextureID(type))) {
    scale(Constants::GridSize / getGlobalBounds().width, Constants::GridSize / getGlobalBounds().height);
}
Tile::~Tile() {}

SceneNode::Ptr TileManager::generateRow(Tile::Type type, const TextureHolder& textures) {
    SceneNode::Ptr row(new SceneNode());
    // row.get()->setPosition(spawnOrigin);
    for (int i = -Constants::TilesRenderedWide; i <= Constants::TilesRenderedWide; i++) {
        SceneNode::Ptr tile(new Tile(type, textures));
        tile.get()->setPosition(i * Constants::GridSize, 0);
        row.get()->attachChild(std::move(tile));
    }
    return std::move(row);
}

TileManager::TileManager() : mSpawnOrigin(0, 0), mTiles(new SceneNode()) {
    // mTiles.get()->setPosition(mSpawnOrigin);
}

TileManager::TileManager(sf::Vector2f spawnOrigin) : mSpawnOrigin(spawnOrigin), mTiles(new SceneNode()) {
    // mTiles.get()->setPosition(mSpawnOrigin);
}

void TileManager::update(sf::FloatRect viewBounds, const TextureHolder& mTextures, const sf::Time& dt) {
    // std::cout << "Spawned row at " << mSpawnOrigin.x << ' ' << mSpawnOrigin.y << '\n';
    while (mSpawnOrigin.y > viewBounds.top) {
        int type = rand() % 3;
        SceneNode::Ptr row = generateRow(static_cast<Tile::Type>(type), mTextures);
        row.get()->setPosition(mSpawnOrigin);
        mTiles.get()->attachChild(std::move(row));
        mSpawnOrigin.y -= Constants::GridSize;
    }
    Command command;
    command.category = Category::Tile;
    command.action = derivedAction<Tile>([this, viewBounds, dt](Tile& tile, sf::Time) {
        if (!viewBounds.intersects(tile.getBoundingRect())) {
            tile.destroy();
        }
    });
    mTiles.get()->onCommand(command, dt);
    mTiles.get()->removeWrecks();
}

void TileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // std::cout << "Drawing tiles\n";
    target.draw(*mTiles, states);
}

void TileManager::checkNodeCollision(sf::FloatRect rect, std::set<SceneNode*>& collisionNodes) {
    mTiles.get()->checkNodeCollision(rect, collisionNodes);
}