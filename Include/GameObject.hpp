#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <TileManagement.hpp>
#include <ObstacleManagement.hpp>
#include <Animation.hpp>

namespace RowObject {
    const static std::vector<std::vector<Tile::Type>> initilizeTileTypes();
    const static std::vector<std::vector<Obstacle::Type>> initilizeObstacleTypes();

    enum Type {
        Sand,
        Grass,
        Ice,
        Log,
        Soil,
        Road,
        Rail,
        Grass2,
        Sand2,
        Sand3,
        Grass3,
        Grass4,
        Road2,
        Rail2,
        Grass5,
        Grass6,
        Grass7,
        TypeCount,
    };

};

class GameObject : public SceneNode {
public:
    GameObject(sf::Vector2f spawnOrigin, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures, std::map<Animations::ID, Animation>& animations);
    virtual void updateCurrent(sf::Time dt);
    void setSpawnOrigin(sf::Vector2f spawnOrigin);
private:
    int last = -1;

    void initialGenerate();
    sf::Vector2f mSpawnOrigin;
    std::function<sf::FloatRect()> getBattlefieldBounds;
    TextureHolder* mTextures;
    SceneNode* mTiles, *mObstacles;
    std::map<Animations::ID, Animation>& mAnimations;
};

#endif // GAMEOBJECT_HPP