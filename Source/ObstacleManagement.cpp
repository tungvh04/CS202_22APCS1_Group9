#include <iostream>
#include <ObstacleManagement.hpp>
#include <DataTables.hpp>
#include <GameLevel.hpp>

namespace ObstacleDataTables {
    const std::vector<ObstacleData> data = initializeObstacleData();
}

Textures::ID toTextureID(Obstacle::Type type) {
    return ObstacleDataTables::data[type].texture;
}

unsigned int Obstacle::getCategory() const {
    switch (mType) {
        case Car:
            return Category::Car | Category::Obstacle;
        case Car1:
            return Category::Car | Category::Obstacle;
        case Oto:
            return Category::Car | Category::Obstacle;
        case Oto_1:
            return Category::Car | Category::Obstacle;
        case Oto1:
            return Category::Car | Category::Obstacle;
        case Oto1_1:
            return Category::Car | Category::Obstacle;
        case Oto2:
            return Category::Car | Category::Obstacle;
        case Oto2_1:
            return Category::Car | Category::Obstacle;    
        case Stone:
            return Category::Stone | Category::Obstacle;
        case Island:
            return Category::Island | Category::Obstacle;
        case Train:
            return Category::Car | Category::Obstacle;
        case Train1:
            return Category::Car | Category::Obstacle;
        case TrafficLightGreen:
            return Category::TrafficLightGreen;
        case TrafficLightRed:
            return Category::TrafficLightRed;
        case TrafficLightYellow:
            return Category::TrafficLightYellow;
        case SlowDown:
            return Category::SlowDown | Category::PickUp | Category::HurtLarge;
        case SpeedUp:
            return Category::SpeedUp | Category::PickUp | Category::Hot | Category::HurtSmall;
        case IceCream:
            return Category::Cold | Category::PickUp | Category::HealLarge;
        case Tree:
            return Category::Stone | Category::Obstacle;
        case Tree1:
            return Category::Stone | Category::Obstacle;
        case Tree2:
            return Category::Stone | Category::Obstacle;
        case Tree3:
            return Category::Stone | Category::Obstacle;
        case Tree4:
            return Category::Stone | Category::Obstacle;
        case Tree5:
            return Category::Stone | Category::Obstacle;
        case Animal1:
            return Category::Car | Category::HurtLarge | Category::PickUp;
        case Animal2:
            return Category::Car | Category::HurtLarge | Category::PickUp;
        case Animal3:
            return Category::Car | Category::HurtLarge | Category::PickUp;
        case Animal4:
            return Category::Car | Category::HurtLarge | Category::PickUp;
        default:
            throw std::runtime_error("Invalid obstacle type");
    }
}

bool Obstacle::isDestroyed() const {
    if (isDestroyedFlag) return true;
    if (isKillByTime()) {
        return getKillTime().asSeconds()<0;
    }
    return !getBattlefieldBounds().intersects(getBoundingRect());
}

sf::FloatRect Obstacle::getBoundingRect() const {
    if (ObstacleDataTables::data[mType].hasAnimation) {
        return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
    }
    else {
        return MovingObject::getBoundingRect();
    }
}

Obstacle::Obstacle(Type type, const TextureHolder& textures, std::function<sf::FloatRect()> getBattlefieldBounds, std::map<Animations::ID, Animation>& animations)
    : mType(type), MovingObject(textures.get(toTextureID(type))), getBattlefieldBounds(getBattlefieldBounds) {
    initializeObstacle();
}

void Obstacle::initializeObstacle() {
    // ...
}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    if (ObstacleDataTables::data[mType].hasAnimation) {
        target.draw(mAnimation, states);
    } else {
        MovingObject::drawCurrent(target, states);
    }
}

void Obstacle::updateCurrent(sf::Time dt) {
    if (ObstacleDataTables::data[mType].hasAnimation) {
        mAnimation.update(dt);
    } else {
        MovingObject::updateCurrent(dt);
    }
}

ObstacleRow::ObstacleRow(std::vector<Obstacle::Type> types, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures, std::map<Animations::ID, Animation>& animation)
    : getBattlefieldBounds(getBattlefieldBounds), mTextures(textures), mAnimations(animation) {
    initializeObstacleRow(types);
}

void ObstacleRow::initializeObstacleRow(std::vector<Obstacle::Type> types) {
    if (ObstacleDataTables::data[type].hasAnimation) {
        mAnimation = animations[ObstacleDataTables::data[type].animation];
    }
    rotate(ObstacleDataTables::data[type].rotateAngle);
    if (ObstacleDataTables::data[type].flipHorizontal) flipHorizontal();
    if (ObstacleDataTables::data[type].flipVertical) flipVertical();
    if (ObstacleDataTables::data[type].scaleX) {
        if (ObstacleDataTables::data[type].scaleY) {
            scale(Constants::GridSize / getGlobalBounds().width, Constants::GridSize / getGlobalBounds().height);
        }   
        else {
            scale(Constants::GridSize / getGlobalBounds().width, Constants::GridSize / getGlobalBounds().width);
        }
    }
    else {
        if (ObstacleDataTables::data[type].scaleY) {
            scale(Constants::GridSize / getGlobalBounds().height, Constants::GridSize / getGlobalBounds().height);
        }
        else {

        }
    }
    if (ObstacleDataTables::data[type].killByTime) {
        setKillTime(ObstacleDataTables::data[type].killTime);
    }
}

sf::FloatRect ObstacleRow::getBoundingRect() const {
    sf::Vector2f position = getWorldPosition();
    position.x -= 1e9;
    position.y -= Constants::GridSize / 2;
    sf::FloatRect rect(position.x, position.y, 2e9, Constants::GridSize);
    return rect;
}

bool ObstacleRow::isDestroyed() const {
    return !getBattlefieldBounds().intersects(getBoundingRect()) | isDestroyedFlag;
}

void ObstacleRow::updateCurrent(sf::Time dt) {
    move(getVelocity() * dt.asSeconds());
    for (int i = 0; i < mChildren.size(); i++) {
        updateObstacleRowChildren(i, dt);
    }
    if (mType == Obstacle::Type::TypeCount) {
        return;
    }
    updateObstacleRow(dt);
}

void ObstacleRow::updateObstacleRowChildren(int i, sf::Time dt) {
    if (ObstacleDataTables::data[mType].hasAnimation) {
        mAnimation.update(dt);
    }
    else {
        MovingObject::updateCurrent(dt);
    }
}

void ObstacleRow::updateObstacleRow(sf::Time dt) {
    move(getVelocity() * dt.asSeconds());
    for (int i=0;i<mChildren.size();i++) {
        if (dynamic_cast<Obstacle&>(*mChildren[i]).getType() == Obstacle::Type::TrafficLightGreen) {
            mChildren[i]->move(-getVelocity() * dt.asSeconds());
        }
        if (dynamic_cast<Obstacle&>(*mChildren[i]).getType() == Obstacle::Type::TrafficLightRed) {
            mChildren[i]->move(-getVelocity() * dt.asSeconds());
        }
    }
    if (mType == Obstacle::Type::TypeCount) {
        return;
    }
    if (mTimeToWait <= sf::Time::Zero) {
        if (!hasSpawned) {
            hasSpawned=true;
            //Green light spawn here
            if (!ObstacleDataTables::data[mType].noTrafficLight) {
                SceneNode::Ptr lightObstacle(new Obstacle(Obstacle::Type::TrafficLightGreen, *mTextures, getBattlefieldBounds, mAnimations));
                float lightLeftBound = getBattlefieldBounds().left + Constants::lightOffset - getPosition().x ;
                float lightRightBound = getBattlefieldBounds().left + getBattlefieldBounds().width - Constants::lightOffset - getPosition().x ;
                if (getVelocity().x > 0) {
                    lightObstacle->setPosition(lightLeftBound, 0);
                }
                else if (getVelocity().x < 0) {
                    lightObstacle->setPosition(lightRightBound, 0);
                }
                lightObstacle->setKillTime(sf::milliseconds(int(randomTimeGroup.asMilliseconds())*(groupSpawnLeft-1))+mTimeToSpawn+sf::seconds(Constants::trafficLightKillDelay)+ObstacleDataTables::data[mType].passTime);
                attachChild(std::move(lightObstacle));
                //-------------------------------------------------
            }
        }
        if (mTimeToSpawn <= sf::Time::Zero) {
            bool isSpawn = rand() % 5;
            if (!isSpawn) {
                return;
            }
            if (getVelocity().x == 0) {
                return;
            }

            SceneNode::Ptr obstacle(new Obstacle(mType, *mTextures, getBattlefieldBounds, mAnimations));
            float leftBound = getBattlefieldBounds().left + ObstacleDataTables::data[mType].spawnOffset - getPosition().x;
            float rightBound = getBattlefieldBounds().left + getBattlefieldBounds().width - ObstacleDataTables::data[mType].spawnOffset - getPosition().x;
            // obstacle->move(leftBound, 0);
            if (getVelocity().x > 0) {
                obstacle->setPosition(leftBound, 0);
            }
            else if (getVelocity().x < 0) {
                obstacle->setPosition(rightBound, 0);
            }
            attachChild(std::move(obstacle));
            groupSpawnLeft--;
            if (groupSpawnLeft==0) {
                sf::Time minTime = ObstacleDataTables::data[mType].minTime;
                sf::Time maxTime = ObstacleDataTables::data[mType].maxTime;
                sf::Time deltaTime = maxTime - minTime;
                int randTime = rand() % (int)deltaTime.asMilliseconds();
                sf::Time randomTime = sf::milliseconds(randTime);
                randomTime += minTime;
                randomTimeGroup = randomTime;
                mTimeToWait = ObstacleDataTables::data[mType].groupDelayTime;
                if (!ObstacleDataTables::data[mType].noTrafficLight) {
                    //Spawn green light here
                    SceneNode::Ptr lightObstacle(new Obstacle(Obstacle::Type::TrafficLightRed, *mTextures, getBattlefieldBounds, mAnimations));
                    float lightLeftBound = getBattlefieldBounds().left - getPosition().x + Constants::lightOffset;
                    float lightRightBound = getBattlefieldBounds().left + getBattlefieldBounds().width - Constants::lightOffset - getPosition().x ;
                    if (getVelocity().x > 0) {
                        lightObstacle->setPosition(lightLeftBound, 0);
                    }
                    else if (getVelocity().x < 0) {
                        lightObstacle->setPosition(lightRightBound, 0);
                    }
                    lightObstacle->setKillTime(randomTimeGroup+mTimeToWait+sf::seconds(Constants::trafficLightKillDelay)-ObstacleDataTables::data[mType].passTime);
                    attachChild(std::move(lightObstacle));
                    //---------------------------------------------
                }
                groupSpawnLeft = ObstacleDataTables::data[mType].groupSpawnAmount;
                hasSpawned=false;
            }
            mTimeToSpawn = randomTimeGroup;
        }
        else mTimeToSpawn -= dt;
    }
    else mTimeToWait -= dt;
}