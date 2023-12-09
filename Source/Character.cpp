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
    mPath.push(direction);
}

void Character::updateCurrent(sf::Time dt) {

    // std::cout << mSprite.getGlobalBounds().width << ' ' << mSprite.getGlobalBounds().height << std::endl;
    if (!mPath.empty()) {
        sf::Vector2f direction = mPath.front();
        move(direction*distancePerCommand);
        sf::Vector2f movement = direction * dt.asSeconds();
        //std::cout<<movement.x<<' '<<movement.y<<' '<<distanceTravelled<<'\n';
        float distanceLeft = distancePerCommand - distanceTravelled;
        /*
        if (std::sqrt(movement.x * movement.x + movement.y * movement.y) > distanceLeft) {
            movement = movement / std::sqrt(movement.x * movement.x + movement.y * movement.y) * distanceLeft;
            distanceTravelled = 0;
            mPath.pop();
        }
        distanceTravelled += std::sqrt(movement.x * movement.x + movement.y * movement.y);
        */
       if (float(movement.x + movement.y) >= distanceLeft) {
            if (movement.x>0) {
                movement.x=distanceLeft;
            }
            if (movement.y>0) {
                movement.y=distanceLeft;
            }
            distanceTravelled = 0;
            mPath.pop();
        }
        distanceTravelled += abs(movement.x+movement.y);
        move(movement);
    }
    move(getVelocity() * dt.asSeconds());
}