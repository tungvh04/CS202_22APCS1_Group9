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
        case Tile::Log:
            return Textures::Log;
        case Tile::Road:
            return Textures::Road;
        case Tile::Rail:
            return Textures::Rail;
        case Tile::Soil:
            return Textures::Soil;
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
        case Log:
            return Category::Ice | Category::Tile;
        case Road:
            return Category::Road | Category::Tile;
        case Rail:
            return Category::Rail | Category::Tile;
        case Soil:
            return Category::Road | Category::Tile;
        default:
            throw std::runtime_error("Invalid tile type");
    }
}
void Tile::destroy() {
    isDestroy = true;
}
bool Tile::isDestroyed() const {
    return isDestroy|isDestroyedFlag;
}
Tile::Tile(Type type, const TextureHolder& textures) : mType(type), MovingObject(textures.get(toTextureID(type))) {
    scale(Constants::GridSize / getGlobalBounds().width, Constants::GridSize / getGlobalBounds().height);
}
Tile::~Tile() {}



TileRow::TileRow(std::vector<Tile::Type> types, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures) : getBattlefieldBounds(getBattlefieldBounds), mTextures(textures) {
    generateRow(types);
}
void TileRow::generateRow(std::vector<Tile::Type> types) {
    for (int i = -Constants::TilesRenderedWide; i <= Constants::TilesRenderedWide; i++) {
        int type = rand() % types.size();
        SceneNode::Ptr tile(new Tile(types[type], *mTextures));
        tile.get()->setPosition(i * Constants::GridSize, 0);
        attachChild(std::move(tile));
    }
}

sf::FloatRect TileRow::getBoundingRect() const {
    sf::Vector2f position = getWorldPosition();
    position.x -= Constants::GridSize * Constants::TilesRenderedWide;
    position.y -= Constants::GridSize / 2;
    sf::FloatRect rect(position.x, position.y, Constants::GridSize * Constants::TilesRenderedWide * 2, Constants::GridSize);
    return rect;
}

bool TileRow::isDestroyed() const {
    return !getBattlefieldBounds().intersects(getBoundingRect())|isDestroyedFlag;
}


TileManager::TileManager(std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures) : mSpawnOrigin(0, 0), getBattlefieldBounds(getBattlefieldBounds), mTextures(textures) {
}


TileManager::TileManager(sf::Vector2f spawnOrigin, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures) : mSpawnOrigin(spawnOrigin), getBattlefieldBounds(getBattlefieldBounds), mTextures(textures) {
}

void TileManager::updateCurrent(sf::Time dt) {
}

void TileManager::setSpawnOrigin(sf::Vector2f spawnOrigin) {
    mSpawnOrigin = spawnOrigin;
}