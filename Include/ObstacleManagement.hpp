#ifndef OBSTACLEMANAGEMENT_HPP
#define OBSTACLEMANAGEMENT_HPP


#include <ResourceIdentifiers.hpp>
#include <MovingObject.hpp>
#include <Const.hpp>
#include <SpriteNode.hpp>
#include <ResourceHolder.hpp>
#include <Category.hpp>
#include <Command.hpp>
#include <Foreach.hpp>

#include <functional>


#include <vector>

class Obstacle : public MovingObject {
public:
    enum Type {
        Car,
        Car1,
        Stone,
        Island,
        Train,
        Train1,
        TrafficLightRed,
        TrafficLightYellow,
        TrafficLightGreen,
        TypeCount,
    };
    
    virtual unsigned int getCategory() const;
    Obstacle(Type type, const TextureHolder& textures, std::function<sf::FloatRect()> getBattlefieldBounds);
    ~Obstacle();
    virtual bool isDestroyed() const;

    Type getType();
private:
    // virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Type mType;
    std::function<sf::FloatRect()> getBattlefieldBounds;
};

class ObstacleRow : public Entity {
public:
    ObstacleRow(std::vector<Obstacle::Type> types, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures);
    virtual void updateCurrent(sf::Time dt);
    sf::FloatRect getBoundingRect() const;
    bool isDestroyed() const;
private:
    std::function<sf::FloatRect()> getBattlefieldBounds;
    TextureHolder* mTextures;
    // std::vector<Obstacle::Type> mTypes;
    Obstacle::Type mType;
    void generateRow();
    sf::Time mTimeToSpawn = sf::seconds(0);
    sf::Time mTimeToWait = sf::seconds(0);

    int groupSpawnLeft;
    int groupSpawnSize;
    sf::Time randomTimeGroup;
    bool hasSpawned = false;
};

#endif // OBSTACLEMANAGEMENT_HPP