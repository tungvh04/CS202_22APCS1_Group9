#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <Entity.hpp>
#include <ResourceIdentifiers.hpp>
#include <Const.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <queue>

class Character : public Entity {
public:
    enum Type {
        Player,
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

private:
    //State hell
    
    bool onWater;
    bool onIsland;


    std::queue<sf::Vector2f> mPath;
    const float mStep = Constants::GridSize;
    virtual void updateCurrent(sf::Time dt);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    bool predictMovement(sf::Vector2f direction);

    Type mType;
    sf::Sprite mSprite;
    sf::Vector2f mGridPosition;

    bool mIsMoving = false;
    sf::Vector2f mMovement;
    float mDistanceTravelled = 0.f;

    SceneNode* worldSceneGraph;

    bool mIsDestroyed = false;
};


#endif // CHARACTER_HPP