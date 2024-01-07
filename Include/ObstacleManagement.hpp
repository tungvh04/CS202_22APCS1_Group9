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
#include <Animation.hpp>

#include <functional>


#include <vector>

class Obstacle : public MovingObject {
public:
    enum Type {
        Car,
        Car1,
        Oto,
        Oto_1,
        Oto1,
        Oto1_1,
        Oto2,
        Oto2_1,
        Stone,
        Island,
        Train,
        Train1,
        TrafficLightRed,
        TrafficLightYellow,
        TrafficLightGreen,
        SpeedUp,
        SlowDown,
        IceCream,
        Tree,
        Tree1,
        Tree2,
        Tree3,
        Tree4,
        Tree5,
        Animal1,
        Animal2,
        Animal3,
        Animal4,
        TypeCount,
        //Honey,
    };
    
    virtual unsigned int getCategory() const;
    Obstacle(Type type, const TextureHolder& textures, std::function<sf::FloatRect()> getBattlefieldBounds, std::map<Animations::ID, Animation>& animations);
    ~Obstacle();
    virtual bool isDestroyed() const;

    Type getType();
    virtual sf::FloatRect getBoundingRect() const;
private:
    virtual void updateCurrent(sf::Time dt);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    // virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Type mType;
    std::function<sf::FloatRect()> getBattlefieldBounds;
    Animation* mAnimation;
};

class ObstacleRow : public Entity {
public:
    ObstacleRow(std::vector<Obstacle::Type> types, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures, std::map<Animations::ID, Animation>& animations);
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
    std::map<Animations::ID, Animation>& mAnimations;
};

#endif // OBSTACLEMANAGEMENT_HPP