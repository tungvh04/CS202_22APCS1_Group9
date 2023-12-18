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

class TileManager : public sf::Drawable {
public:
    TileManager();
    explicit TileManager(sf::Vector2f spawnOrigin);
    void update(sf::FloatRect viewBounds, const TextureHolder& mTextures, const sf::Time& dt);
    void checkNodeCollision(sf::FloatRect rect, std::set<SceneNode*>& collisionNodes);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    SceneNode::Ptr generateRow(Tile::Type type, const TextureHolder& textures);
    sf::Vector2f mSpawnOrigin;
    SceneNode::Ptr mTiles;
};

#endif // TILEMANAGEMENT_HPP