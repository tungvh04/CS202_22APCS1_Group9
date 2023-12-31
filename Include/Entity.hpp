#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SceneNode.hpp>
#include <CommandQueue.hpp>

class Entity : public SceneNode {

public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);
    sf::Vector2f getVelocity() const;
    
    sf::Time killTime;
    bool killByTime;

protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
    virtual void updateCurrent(sf::Time dt);

    sf::Vector2f mVelocity;
};

#endif // ENTITY_HPP