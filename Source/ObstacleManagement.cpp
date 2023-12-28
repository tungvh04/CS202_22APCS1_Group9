#include <iostream>

#include <ObstacleManagement.hpp>
#include <DataTables.hpp>

namespace ObstacleDataTables {
    const std::vector<ObstacleData> data = initializeObstacleData();
};

Textures::ID toTextureID(Obstacle::Type type) {
    return ObstacleDataTables::data[type].texture;
    switch (type) {
        case Obstacle::Car:
            return Textures::Car;
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
        default:
            throw std::runtime_error("Invalid obstacle type");
    }
}

bool Obstacle::isDestroyed() const {
    return !getBattlefieldBounds().intersects(getBoundingRect());
}


Obstacle::Obstacle(Type type, const TextureHolder& textures, std::function<sf::FloatRect()> getBattlefieldBounds) : mType(type), MovingObject(textures.get(toTextureID(type))), getBattlefieldBounds(getBattlefieldBounds) {
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
    
}

Obstacle::~Obstacle() {}

ObstacleRow::ObstacleRow(std::vector<Obstacle::Type> types, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures) : getBattlefieldBounds(getBattlefieldBounds), mTextures(textures) {
    if (types.empty()) {
        mType = Obstacle::Type::TypeCount;
        return;
    }
    mType = types[rand() % types.size()];
    setVelocity(ObstacleDataTables::data[mType].speed);
    generateRow();
}

void ObstacleRow::generateRow() {

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

void ObstacleRow::updateCurrent(sf::Time dt) {
    // Entity::updateCurrent(dt);
    // std::cout << "This row is at " << getPosition().y << std::endl;
    move(getVelocity() * dt.asSeconds());
    if (mType == Obstacle::Type::TypeCount) {
        return;
    }
    if (mTimeToSpawn <= sf::Time::Zero) {
        bool isSpawn = rand() % 5;
        if (!isSpawn) {
            return;
        }
        SceneNode::Ptr obstacle(new Obstacle(mType, *mTextures, getBattlefieldBounds));
        float leftBound = getBattlefieldBounds().left - getPosition().x;
        float rightBound = getBattlefieldBounds().left + getBattlefieldBounds().width - getPosition().x;
        // obstacle->move(leftBound, 0);
        if (getVelocity().x > 0) {
            obstacle->setPosition(leftBound, 0);
        }
        else {
            obstacle->setPosition(rightBound, 0);
        }
        attachChild(std::move(obstacle));
        sf::Time minTime = ObstacleDataTables::data[mType].minTime;
        sf::Time maxTime = ObstacleDataTables::data[mType].maxTime;
        sf::Time deltaTime = maxTime - minTime;
        int randTime = rand() % (int)deltaTime.asMilliseconds();
        sf::Time randomTime = sf::milliseconds(randTime);
        randomTime += minTime;
        mTimeToSpawn = randomTime;
    }
    else mTimeToSpawn -= dt;
}