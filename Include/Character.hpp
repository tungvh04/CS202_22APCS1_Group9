#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>
#include <Const.hpp>
#include <Animation.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <queue>

class Character : public Entity {
public:
    enum Type {
        Player,
        BlueDino,
        GreenDino,
        YellowDino,
        RedDino,
        BlueFrog,
        GreenFrog,
        YellowFrog,
        PinkFrog
    };

    Character(Type type, const TextureHolder& textures);
    virtual unsigned int getCategory() const;
    void pathRequest(sf::Vector2f direction);
    virtual sf::FloatRect getBoundingRect() const;
    virtual bool isMarkedForRemoval() const;
    void clearState();
    void setWater();
    void setIsland();
    bool deadOnWater();

    void setWorldSceneGraph(SceneNode* worldSceneGraph);
    void destroy();
    virtual bool isDestroyed() const;


    //void setSpeedMult(float speedMult);

    void setFreezing();
    void notFreezing();
    bool isFreezing();
    bool isBurning();

    float getTemperature();
    void shiftTemperature(float offset);
    void setTemperature(float value);
    void setDefaultTemperature(float value);
    void updateTemperature(sf::Time dt);

    float getSpeedMult();
    void shiftSpeedMult(float offset);
    void multSpeedMult(float offset);
    void setSpeedMult(float value);
    void setDefaultSpeedMult(float value);
    void updateSpeedMult(sf::Time dt);

    float getHealth();
    void hurt(float x);
    void updateHealth(sf::Time dt);

private:
    //State hell
    
    bool onWater;
    bool onIsland;

    bool isCold;

    float temperature;
    float defaultTemperature;

    float speedMult = 1.0;
    float defaultSpeedMult = 1.0;

    std::queue<sf::Vector2f> mPath;
    const float mStep = Constants::GridSize;
    virtual void updateCurrent(sf::Time dt);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateRollAnimation();

    bool predictMovement(sf::Vector2f direction);
    
    Animation mDeath;
    Animation mMoving;
    
    Type mType;
    sf::Sprite mSprite;
    sf::Vector2f mGridPosition;

    bool mIsMoving = false;
    bool mShowDeath = false;
    sf::Vector2f mMovement;
    float mDistanceTravelled = 0.f;

    SceneNode* worldSceneGraph;

    bool mIsDestroyed = false;
    enum Facing {
        Left,
        Right
    };
    Facing mFacing = Facing::Right;

    float health;
};


#endif // CHARACTER_HPP