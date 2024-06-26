#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SceneNode.hpp>
#include <CommandQueue.hpp>

class Entity : public SceneNode {

public:
    virtual void setVelocity(sf::Vector2f velocity);
    virtual void setVelocity(float vx, float vy);
    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);
    sf::Vector2f getVelocity() const;

protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

protected:
    virtual void updateCurrent(sf::Time dt);

    sf::Vector2f mVelocity;
};

#endif // ENTITY_HPP