#include <Character.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <iostream>
#include <set>

Textures::ID toTextureID(Character::Type type) {
    switch (type) {
        case Character::Player:
            return Textures::Player;
    }
    return Textures::Player;
}

Character::Character(Type type, const TextureHolder& textures) : mType(type), mSprite(textures.get(toTextureID(type))) {
    mSprite.scale(mStep / mSprite.getLocalBounds().width, mStep / mSprite.getLocalBounds().height);
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
    // if (mPath.empty()) mGridPosition = getPosition();
    if (mPath.size() < 2)
        mPath.push(direction);
}

void Character::updateCurrent(sf::Time dt) {
    if (!mIsMoving) {
        mGridPosition = getPosition();
        if (!mPath.empty()) {
            sf::Vector2f direction = mPath.front();
            mPath.pop();
            if (!predictMovement(direction)) {
                return;
            }
            mMovement = direction;
            mIsMoving = true;
        }
    }
    if (mIsMoving) {
        sf::Vector2f movement = mMovement * dt.asSeconds();
        if (mDistanceTravelled + abs(movement.x) > mStep) {
            mDistanceTravelled = 0.f;
            mIsMoving = false;
            if (movement.x > 0) {
                mGridPosition.x += mStep;
            }
            else {
                mGridPosition.x -= mStep;
            }
            setPosition(mGridPosition);
        }
        else if (mDistanceTravelled + abs(movement.y) > mStep) {
            mDistanceTravelled = 0.f;
            mIsMoving = false;
            if (movement.y > 0) {
                mGridPosition.y += mStep;
            }
            else {
                mGridPosition.y -= mStep;
            }
            setPosition(mGridPosition);
        }
        else {
            mDistanceTravelled += abs(movement.x) + abs(movement.y);
            move(movement);
        }
    }
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

void Character::setWorldSceneGraph(SceneNode* worldSceneGraph) {
    this->worldSceneGraph = worldSceneGraph;
}

bool Character::predictMovement(sf::Vector2f direction) {
    sf::FloatRect bounds = getBoundingRect();
    if (direction.x < 0) {
        bounds.left -= mStep;
    }
    else if (direction.x > 0) {
        bounds.left += mStep;
    }
    else if (direction.y < 0) {
        bounds.top -= mStep;
    }
    else if (direction.y > 0) {
        bounds.top += mStep;
    }

    std::set<SceneNode*> collidingNodes;
    worldSceneGraph->checkNodeCollision(bounds, collidingNodes);

    auto matchesCategories = [](SceneNode* node, Category::Type type) {
        return (node->getCategory() & type) != 0;
    };

    for (auto node : collidingNodes) {
        if (matchesCategories(node, Category::Stone)) {
            return false;
        }
    }
    return true;
}