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
    
    void setKillTime(sf::Time dt);
    bool isKillByTime() const;
    sf::Time getKillTime() const;

protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
    virtual void updateCurrent(sf::Time dt);

    sf::Vector2f mVelocity;

    sf::Time killTime;
    bool killByTime;
};

#endif // ENTITY_HPP