#ifndef TILEMANAGEMENT_HPP
#define TILEMANAGEMENT_HPP

// #include <Tile.hpp>
#include <ResourceIdentifiers.hpp>
#include <MovingObject.hpp>
#include <Const.hpp>
#include <SpriteNode.hpp>
#include <ResourceHolder.hpp>
#include <Category.hpp>
#include <Command.hpp>
#include <functional>


#include <vector>

class Tile : public MovingObject {
public:
    enum Type {
        Grass,
        Sand,
        Ice,
    };
    unsigned int getCategory() const;
    Tile(Type type, const TextureHolder& textures);
    ~Tile();
    void destroy();
    bool isDestroyed() const;

private:
    Type mType;
    bool isDestroy = false;
};

class TileRow : public SceneNode {
public:
    TileRow(std::vector<Tile::Type> types, std::function<sf::FloatRect()> getBoundingRect, TextureHolder* textures);
    void update(sf::Time dt);
    sf::FloatRect getBoundingRect() const;
    bool isDestroyed() const;
private:
    std::function<sf::FloatRect()> getBattlefieldBounds;
    TextureHolder* mTextures;
    void generateRow(std::vector<Tile::Type> types);
};

class TileManager : public SceneNode {
public:
    TileManager(std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures);
    TileManager(sf::Vector2f spawnOrigin, std::function<sf::FloatRect()> getBoundingRect, TextureHolder* textures);
    void updateCurrent(sf::Time dt);
    void setSpawnOrigin(sf::Vector2f spawnOrigin);
private:
    sf::Vector2f mSpawnOrigin;
    std::function<sf::FloatRect()> getBattlefieldBounds;
    TextureHolder* mTextures;
};

#endif // TILEMANAGEMENT_HPP