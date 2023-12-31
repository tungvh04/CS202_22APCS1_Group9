#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <TileManagement.hpp>
#include <ObstacleManagement.hpp>

namespace RowObject {
    const static std::vector<std::vector<Tile::Type>> initilizeTileTypes();
    const static std::vector<std::vector<Obstacle::Type>> initilizeObstacleTypes();

    enum Type {
        Sand,
        Grass,
        Ice,
        Road,
        Rail,
        TypeCount,
    };

};

class GameObject : public SceneNode {
public:
    GameObject(sf::Vector2f spawnOrigin, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures);
    virtual void updateCurrent(sf::Time dt);
    void setSpawnOrigin(sf::Vector2f spawnOrigin);
private:
    sf::Vector2f mSpawnOrigin;
    std::function<sf::FloatRect()> getBattlefieldBounds;
    TextureHolder* mTextures;
    SceneNode* mTiles, *mObstacles;
};

#endif // GAMEOBJECT_HPP