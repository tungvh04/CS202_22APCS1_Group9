#include <Entity.hpp>

void Entity::setVelocity(sf::Vector2f velocity) {
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
    return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity) {
    mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy) {
    mVelocity.x += vx;
    mVelocity.y += vy;
}

void Entity::updateCurrent(sf::Time dt) {
    if (killByTime) {
        killTime-=dt;
        if (killTime.asSeconds()<0) {
            //kill here
            return;
        }
    }
    move(mVelocity * dt.asSeconds());
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{	
    if (killByTime) {
        killTime-=dt;
        if (killTime.asSeconds()<0) {
            //kill here
            return;
        }
    }
	move(mVelocity * dt.asSeconds());
}