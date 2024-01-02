#include <iostream>

#include <ObstacleManagement.hpp>
#include <DataTables.hpp>


#include <GameLevel.hpp>
namespace ObstacleDataTables {
    const std::vector<ObstacleData> data = initializeObstacleData();
};

Textures::ID toTextureID(Obstacle::Type type) {
    return ObstacleDataTables::data[type].texture;
    switch (type) {
        case Obstacle::Car:
            return Textures::Car;
        case Obstacle::Train:
            return Textures::Train;
        case Obstacle::Island:
            return Textures::Island;
        case Obstacle::TrafficLightGreen:
            return Textures::TrafficLightGreen;
        case Obstacle::TrafficLightRed:
            return Textures::TrafficLightRed;
        case Obstacle::TrafficLightYellow:
            return Textures::TrafficLightYellow;
        default:
            throw std::runtime_error("Invalid obstacle type");
    }
}

unsigned int Obstacle::getCategory() const {
    switch (mType) {
        case Car:
            return Category::Car | Category::Obstacle;
        case Car1:
            return Category::Car | Category::Obstacle;
        case Stone:
            return Category::Stone | Category::Obstacle;
        case Island:
            return Category::Island;
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
        default:
            throw std::runtime_error("Invalid obstacle type");
    }
}

bool Obstacle::isDestroyed() const {
    if (isKillByTime()) {
        return getKillTime().asSeconds()<0;
    }
    return !getBattlefieldBounds().intersects(getBoundingRect());
}


Obstacle::Obstacle(Type type, const TextureHolder& textures, std::function<sf::FloatRect()> getBattlefieldBounds) : mType(type), MovingObject(textures.get(toTextureID(type))), getBattlefieldBounds(getBattlefieldBounds) {
    rotate(ObstacleDataTables::data[type].rotateAngle);
    if (ObstacleDataTables::data[type].flipHorizontal) flipHorizontal();
    if (ObstacleDataTables::data[type].flipVertical) flipVertical();
    // std::cout << "Texture loaded is " << toTextureID(type) << std::endl;
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
            //scale(Constants::GridSize / getGlobalBounds().width, Constants::GridSize / getGlobalBounds().height);
        }
    }
    if (ObstacleDataTables::data[type].killByTime) {
        setKillTime(ObstacleDataTables::data[type].killTime);
    }
}

Obstacle::~Obstacle() {
    if (Type::TrafficLightGreen==mType) {
        std::cout<<"Green Light destroy at "<<getPosition().x<<' '<<getPosition().y<<'\n';
    }
    if (Type::TrafficLightRed==mType) {
        std::cout<<"Red light destroy at "<<getPosition().x<<' '<<getPosition().y<<'\n';
    }
    if (Type::TrafficLightYellow==mType) {
        std::cout<<"Destroy at "<<getPosition().x<<' '<<getPosition().y<<'\n';
    }
    if (Type::Car==mType) {
        std::cout<<"Car destroy at "<<getPosition().x<<' '<<getPosition().y<<'\n';
    }
}

ObstacleRow::ObstacleRow(std::vector<Obstacle::Type> types, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures) : getBattlefieldBounds(getBattlefieldBounds), mTextures(textures) {
    if (types.empty()) {
        mType = Obstacle::Type::TypeCount;
        return;
    }
    mType = types[rand() % types.size()];
    groupSpawnSize = ObstacleDataTables::data[mType].groupSpawnAmount;
    if (groupSpawnSize==0) {
        groupSpawnSize=1;
    }
    groupSpawnLeft = groupSpawnSize;
    sf::Time minTime = ObstacleDataTables::data[mType].minTime;
    sf::Time maxTime = ObstacleDataTables::data[mType].maxTime;
    if (minTime!=maxTime) {
        sf::Time deltaTime = maxTime - minTime;
        int randTime = rand() % (int)deltaTime.asMilliseconds();
        sf::Time randomTime = sf::milliseconds(randTime);
        randomTime += minTime;
        randomTimeGroup = randomTime;
    }
    sf::Vector2f velocity = ObstacleDataTables::data[mType].speed;
    velocity *= gameLevel.getSpeedMultiplier();
    setVelocity(velocity);
    generateRow();
}

void ObstacleRow::generateRow() {
    if (mType == Obstacle::Type::TypeCount) {
        return;
    }
    if (ObstacleDataTables::data[mType].maxDistance == 0 || ObstacleDataTables::data[mType].minDistance == 0) return;
    int delta = rand() % ObstacleDataTables::data[mType].maxDistance;
    for (int i = -Constants::TilesRenderedWide; i <= Constants::TilesRenderedWide; i++) {
        // int type = rand() % types.size();
        // SceneNode::Ptr tile(new Tile(types[type], *mTextures));
        // tile.get()->setPosition(i * Constants::GridSize, 0);
        // attachChild(std::move(tile));
        if (delta == 0) {
            SceneNode::Ptr obstacle(new Obstacle(mType, *mTextures, getBattlefieldBounds));
            obstacle.get()->setPosition(i * Constants::GridSize, 0);
            attachChild(std::move(obstacle));
            delta = ObstacleDataTables::data[mType].minDistance + rand() % (ObstacleDataTables::data[mType].maxDistance - ObstacleDataTables::data[mType].minDistance);
        }
        else delta--;
    }
}

sf::FloatRect ObstacleRow::getBoundingRect() const {
    sf::Vector2f position = getWorldPosition();
    // position.x -= Constants::GridSize * Constants::TilesRenderedWide;
    position.x -= 1e9;
    position.y -= Constants::GridSize / 2;
    // sf::FloatRect rect(position.x, position.y, Constants::GridSize * Constants::TilesRenderedWide * 2, Constants::GridSize);
    sf::FloatRect rect(position.x, position.y, 2e9, Constants::GridSize);
    return rect;
}

bool ObstacleRow::isDestroyed() const {
    return !getBattlefieldBounds().intersects(getBoundingRect());
}

Obstacle::Type Obstacle::getType() {
    return mType;
}

void ObstacleRow::updateCurrent(sf::Time dt) {
    // Entity::updateCurrent(dt);
    // std::cout << "This row is at " << getPosition().y << std::endl;
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
            //Red light spawn here
            SceneNode::Ptr lightObstacle(new Obstacle(Obstacle::Type::TrafficLightRed, *mTextures, getBattlefieldBounds));
            float lightLeftBound = getBattlefieldBounds().left + Constants::lightOffset - getPosition().x ;
            float lightRightBound = getBattlefieldBounds().left + getBattlefieldBounds().width - Constants::lightOffset - getPosition().x ;
            if (getVelocity().x > 0) {
                //lightObstacle->setPosition(Constants::lightOffsetLeft, 0);
                lightObstacle->setPosition(lightLeftBound, 0);
            }
            else if (getVelocity().x < 0) {
                //lightObstacle->setPosition(Constants::lightOffsetRight,  0);
                lightObstacle->setPosition(lightRightBound, 0);
            }
            lightObstacle->setKillTime(sf::milliseconds(int(randomTimeGroup.asMilliseconds())*groupSpawnLeft)+mTimeToSpawn+sf::seconds(Constants::trafficLightKillDelay));
            std::cout<<"Traffic light red spawn at "<<lightObstacle->getPosition().x<<' '<<lightObstacle->getPosition().y<<" for "<<lightObstacle->getKillTime().asMilliseconds()<<" ms. Each vehicle spawn after "<<randomTimeGroup.asMilliseconds()<<" ms for "<<groupSpawnSize<<" vehicles."<<'\n';
                
            //std::cout<<"Traffic light red spawn at "<<lightObstacle->getPosition().x<<' '<<lightObstacle->getPosition().y<<" for "<<lightObstacle->getKillTime().asMilliseconds()<<" ms."<<'\n';
            attachChild(std::move(lightObstacle));
            //-------------------------------------------------
        }
        if (mTimeToSpawn <= sf::Time::Zero) {
            bool isSpawn = rand() % 5;
            if (!isSpawn) {
                return;
            }
            if (getVelocity().x == 0) {
                return;
            }
            SceneNode::Ptr obstacle(new Obstacle(mType, *mTextures, getBattlefieldBounds));
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
            /*
            sf::Time minTime = ObstacleDataTables::data[mType].minTime;
            sf::Time maxTime = ObstacleDataTables::data[mType].maxTime;
            sf::Time deltaTime = maxTime - minTime;
            int randTime = rand() % (int)deltaTime.asMilliseconds();
            sf::Time randomTime = sf::milliseconds(randTime);
            randomTime += minTime;
            */
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
                //Spawn green light here
                SceneNode::Ptr lightObstacle(new Obstacle(Obstacle::Type::TrafficLightGreen, *mTextures, getBattlefieldBounds));
                float lightLeftBound = getBattlefieldBounds().left - getPosition().x + Constants::lightOffset;
                float lightRightBound = getBattlefieldBounds().left + getBattlefieldBounds().width - Constants::lightOffset - getPosition().x ;
                if (getVelocity().x > 0) {
                    //lightObstacle->setPosition(Constants::lightOffsetLeft, 0);
                    lightObstacle->setPosition(lightLeftBound, 0);
                }
                else if (getVelocity().x < 0) {
                    //lightObstacle->setPosition(Constants::lightOffsetRight,  0);
                    lightObstacle->setPosition(lightRightBound, 0);
                }
                lightObstacle->setKillTime(mTimeToWait+sf::seconds(Constants::trafficLightKillDelay));
                std::cout<<"Traffic light green spawn at "<<lightObstacle->getPosition().x<<' '<<lightObstacle->getPosition().y<<" for "<<lightObstacle->getKillTime().asMilliseconds()<<" ms. Each vehicle spawn after "<<randomTimeGroup.asMilliseconds()<<" ms for "<<groupSpawnSize<<" vehicles."<<'\n';
                //std::cout<<"Traffic light green spawn at "<<lightObstacle->getPosition().x<<' '<<lightObstacle->getPosition().y<<'\n';
                attachChild(std::move(lightObstacle));
                //---------------------------------------------
                groupSpawnLeft = ObstacleDataTables::data[mType].groupSpawnAmount;
                hasSpawned=false;
            }
            mTimeToSpawn = randomTimeGroup;
        }
        else mTimeToSpawn -= dt;
    }
    else mTimeToWait -= dt;
}