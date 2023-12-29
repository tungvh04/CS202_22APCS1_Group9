#include <Character.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <iostream>

Textures::ID toTextureID(Character::Type type) {
    switch (type) {
        case Character::Player:
            return Textures::Player;
    }
    return Textures::Player;
}

Character::Character(Type type, const TextureHolder& textures) : mType(type), mSprite(textures.get(toTextureID(type))) {
    mSprite.scale(distancePerCommand / mSprite.getLocalBounds().width, distancePerCommand / mSprite.getLocalBounds().height);
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

unsigned int Character::getCategory() const {
    switch (mType) {
        case Player:
            return Category::PlayerCharacter;
        default:
            return Category::Object;
    }
}

void Character::pathRequest(sf::Vector2f direction) {
    if (mPath.empty()) mGridPosition = getPosition();
    mPath.push(direction);
}

void Character::updateCurrent(sf::Time dt) {
    // std::cout << mSprite.getGlobalBounds().width << ' ' << mSprite.getGlobalBounds().height << std::endl;
    // std::cout << "Position: " << getPosition().x << ' ' << getPosition().y << std::endl;
    // std::cout << "The player position is " << getWorldPosition().x << ',' << getWorldPosition().y << std::endl;
    if (!mPath.empty()) {
        sf::Vector2f direction = mPath.front();
        sf::Vector2f movement = direction * dt.asSeconds();
        float distanceLeft = distancePerCommand - distanceTravelled;
        if (std::sqrt(movement.x * movement.x + movement.y * movement.y) > distanceLeft) {
            // // movement = movement / std::sqrt(movement.x * movement.x + movement.y * movement.y) * distanceLeft;
            // if (movement.x == 0) movement.y = distanceLeft;
            // else if (movement.y == 0) movement.x = distanceLeft;
            // else {
                // float ratio = std::abs(movement.x / movement.y);
                // movement.x = std::sqrt(distanceLeft * distanceLeft / (1 + ratio * ratio));
                // movement.y = std::sqrt(distanceLeft * distanceLeft - movement.x * movement.x);
            // }
            // assert(std::sqrt(movement.x * movement.x + movement.y * movement.y) == distanceLeft);
            // assert(movement.x == distanceLeft || movement.y == distanceLeft);
            // std::cout << "Movement: " << movement.x << ' ' << movement.y << std::endl;
            distanceTravelled = 0;
            if (movement.x == 0) movement.y = movement.y > 0 ? distancePerCommand : -distancePerCommand;
            else if (movement.y == 0) movement.x = movement.x > 0 ? distancePerCommand : -distancePerCommand;
            else {
                float ratio = std::abs(movement.x / movement.y);
                movement.x = movement.x > 0 ? std::sqrt(distanceLeft * distanceLeft / (1 + ratio * ratio)) : -std::sqrt(distanceLeft * distanceLeft / (1 + ratio * ratio));
                movement.y = movement.y > 0 ? std::sqrt(distanceLeft * distanceLeft - movement.x * movement.x) : -std::sqrt(distanceLeft * distanceLeft - movement.x * movement.x);
            }
            mGridPosition += movement;
            // std::cout << "Grid position: " << mGridPosition.x << ' ' << mGridPosition.y << std::endl;
            setPosition(mGridPosition);
            mPath.pop();
        }
        else {
            distanceTravelled += std::sqrt(movement.x * movement.x + movement.y * movement.y);
            move(movement);
        }
    }
    move(getVelocity() * dt.asSeconds());
}
sf::FloatRect Character::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Character::isMarkedForRemoval() const
{
	//return isDestroyed() && (mExplosion.isFinished() || !mShowExplosion);
    return false;
}