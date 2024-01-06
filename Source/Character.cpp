#include <Character.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <CharacterState.hpp>

#include <cmath>
#include <iostream>
#include <set>

Textures::ID toTextureIDMoving(Character::Type type) {
    switch (type) {
        case Character::BlueDino:
            return Textures::BlueDino;
        case Character::RedDino:
            return Textures::RedDino;
        case Character::YellowDino:
            return Textures::YellowDino;
        case Character::GreenDino:
            return Textures::GreenDino;
        case Character::BlueFrog:
            return Textures::BlueFrog;
        case Character::GreenFrog:
            return Textures::GreenFrog;
        case Character::PinkFrog:
            return Textures::PinkFrog;
        case Character::YellowFrog:
            return Textures::YellowFrog;
    }
    return Textures::Player;
}
Textures::ID toTextureIDDeath(Character::Type type) {
    switch (type) {
        case Character::BlueDino:
            return Textures::BlueDinoDeath;
        case Character::RedDino:
            return Textures::RedDinoDeath;
        case Character::YellowDino:
            return Textures::YellowDinoDeath;
        case Character::GreenDino:
            return Textures::GreenDinoDeath;
        case Character::BlueFrog:
            return Textures::BlueFrogDeath;
        case Character::GreenFrog:
            return Textures::GreenFrogDeath;
        case Character::PinkFrog:
            return Textures::PinkFrogDeath;
        case Character::YellowFrog:
            return Textures::YellowFrogDeath;
    }
    return Textures::Player;
}
Character::Type setType(TypeCharacter::ID type){
    switch (type) {
        case TypeCharacter::BlueDino:
            return Character::Type::BlueDino;
        case TypeCharacter::RedDino:
            return Character::Type::RedDino;
        case TypeCharacter::GreenDino:
            return Character::Type::GreenDino;
        case TypeCharacter::YellowDino:
            return Character::Type::YellowDino;
        case TypeCharacter::BlueFrog:
            return Character::Type::BlueFrog;
        case TypeCharacter::GreenFrog:
            return Character::Type::GreenFrog;
        case TypeCharacter::YellowFrog:
            return Character::Type::YellowFrog;
        case TypeCharacter::PinkFrog:
            return Character::Type::PinkFrog;
        default:
            throw "Not found type characrer";
    }
}
int getSizeFrame(Character::Type type){
    switch (type)
    {
    case Character::BlueDino:
        return 24;
    case Character::RedDino:
        return 24;
    case Character::YellowDino:
        return 24;
    case Character::GreenDino:
        return 24;
    case Character::BlueFrog:
        return 16;
    case Character::YellowFrog:
        return 16;
    case Character::PinkFrog:
        return 16;
    case Character:: GreenFrog:
        return 16;
    }
}
Character::Character(Type type, const TextureHolder& textures) : mSprite(textures.get(Textures::Player)) {
    
    mType = setType(typeCharacter);
    mDeath.setTexture(textures.get(toTextureIDDeath(mType)));
    mMoving.setTexture(textures.get(toTextureIDMoving(mType)));

    int framSize = getSizeFrame(mType);
    mDeath.setFrameSize(sf::Vector2i(framSize, framSize));
    mDeath.setNumFrames(8);
    mDeath.setDuration(sf::seconds(1));

    mMoving.setFrameSize(sf::Vector2i(framSize, framSize));
    mMoving.setNumFrames(8);
    mMoving.setDuration(sf::seconds(0.2));

    mDeath.setOrigin(mDeath.getLocalBounds().width / 2.f, mDeath.getLocalBounds().height / 2.f);
    mDeath.scale(mStep / mDeath.getLocalBounds().width, mStep / mDeath.getLocalBounds().height);
    mMoving.setOrigin(mMoving.getLocalBounds().width / 2.f, mMoving.getLocalBounds().height / 2.f);
    mMoving.scale(mStep / mMoving.getLocalBounds().width, mStep / mMoving.getLocalBounds().height);

    mSprite.scale(mStep / mSprite.getLocalBounds().width, mStep / mSprite.getLocalBounds().height);
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    if (mFacing == Facing::Left) {
        states.transform.scale(-1.f, 1.f);
    }
    if (isDestroyed() && !mIsMoving) target.draw(mDeath, states);
    else {
        target.draw(mMoving, states);
        // target.draw(mSprite, states);
        
    }
}

unsigned int Character::getCategory() const {
    switch (mType) {
        case Player:
            return Category::PlayerCharacter;
        default:
            return Category::PlayerCharacter;
    }
}

void Character::pathRequest(sf::Vector2f direction) {
    if (mPath.size() < 2)
        mPath.push(direction);
}

void Character::updateCurrent(sf::Time dt) {
    if (isDestroyed() && !mIsMoving){
        mDeath.update(dt);
        return;
    }
    if (!mIsMoving) {;
        mGridPosition = getPosition();
        if (!mPath.empty()) {
            sf::Vector2f direction = mPath.front();
            mPath.pop();
            if (!predictMovement(direction)) {
                return;
            }
            mMovement = direction;
            mIsMoving = true;
            if (mMovement.x > 0) {
                mFacing = Facing::Right;
            }
            else if (mMovement.x < 0) {
                mFacing = Facing::Left;
            }
        }
    }
    mMoving.update(dt);
    if (mIsMoving) {
        if (mMoving.isFinished()){
            mMoving.restart();
            return;
        }
        sf::Vector2f movement = mMovement * dt.asSeconds() * speedMult;
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
    updateTemperature(dt);
    updateSpeedMult(dt);
}
sf::FloatRect Character::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Character::isMarkedForRemoval() const
{
	//return isDestroyed() && (mExplosion.isFinished() || !mShowExplosion);
    // return false;
	return isDestroyed() && (mDeath.isFinished() || !mShowDeath);
    return false;
    return isDestroyed();
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

void Character::destroy() {
    // std::cout << "Character destroyed\n";
    if (!mIsDestroyed) {
        mIsDestroyed = true;
        mShowDeath = true;
        mDeath.restart();
    }
}

bool Character::isDestroyed() const {
    return mIsDestroyed|isDestroyedFlag;
}

void Character::setWater() {
    onWater=true;
}

void Character::setIsland() {
    onIsland=true;
}

bool Character::deadOnWater() {
    if (onWater&&!onIsland) return true;
    return false;
}

void Character::clearState() {
    onWater=false;
    onIsland=false;
}
void Character::updateRollAnimation(){
}

/*
void Character::setSpeedMult(float x) {
    speedMult=x;
}
*/
void Character::setFreezing() {
    isCold=true;
}

void Character::notFreezing() {
    isCold=false;
}

bool Character::isFreezing() {
    return getTemperature()<Constants::freezeLimit;
}

bool Character::isBurning() {
    return getTemperature()>Constants::burningLimit;
}

float Character::getTemperature() {
    return temperature;
}

void Character::shiftTemperature(float offset) {
    temperature+=offset;
}

void Character::setTemperature(float value) {
    temperature=value;
}

void Character::setDefaultTemperature(float value) {
    defaultTemperature=value;
}

void Character::updateTemperature(sf::Time dt) {
    temperature-=(temperature-defaultTemperature)*(dt.asMilliseconds()/(dt.asMilliseconds()+Constants::TemperatureSlope));
}

float Character::getSpeedMult() {
    return speedMult;
}

void Character::shiftSpeedMult(float offset) {
    speedMult+=offset;
}

void Character::multSpeedMult(float offset) {
    speedMult*=offset;
}

void Character::setSpeedMult(float value) {
    speedMult=value;
}

void Character::setDefaultSpeedMult(float value) {
    defaultSpeedMult=value;
}

void Character::updateSpeedMult(sf::Time dt) {
    if (isFreezing()) {
        setDefaultSpeedMult(Constants::FreezingDefaultSpeed);
    }
    else if (isBurning()) {
        setDefaultSpeedMult(Constants::BurningDefaultSpeed);
    }
    else {
        setDefaultSpeedMult(1);
    }
    speedMult-=(speedMult-defaultSpeedMult)*(dt.asMilliseconds()/(dt.asMilliseconds()+Constants::SpeedSlope));
}