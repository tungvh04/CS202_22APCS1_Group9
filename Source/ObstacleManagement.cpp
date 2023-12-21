#include <iostream>

#include <ObstacleManagement.hpp>


Textures::ID toTextureID(Obstacle::Type type) {
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
        default:
            throw std::runtime_error("Invalid obstacle type");
    }
}

bool Obstacle::isDestroyed() const {
    return !getBattlefieldBounds().intersects(getBoundingRect());
}


Obstacle::Obstacle(Type type, const TextureHolder& textures, std::function<sf::FloatRect()> getBattlefieldBounds) : mType(type), MovingObject(textures.get(toTextureID(type))), getBattlefieldBounds(getBattlefieldBounds) {
    // std::cout << "Texture loaded is " << toTextureID(type) << std::endl;
    scale(Constants::GridSize / getGlobalBounds().width, Constants::GridSize / getGlobalBounds().height);
}

Obstacle::~Obstacle() {}

ObstacleRow::ObstacleRow(sf::Vector2f rowSpeed, std::vector<Obstacle::Type> types, std::function<sf::FloatRect()> getBattlefieldBounds, TextureHolder* textures) : getBattlefieldBounds(getBattlefieldBounds), mTextures(textures), mTypes(types) {
    setVelocity(rowSpeed);
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
    if (mTypes.empty()) {
        return;
    }
    if (mTimeToSpawn <= sf::Time::Zero) {
        bool isSpawn = rand() % 5;
        if (!isSpawn) {
            return;
        }
        int type = rand() % mTypes.size();
        SceneNode::Ptr obstacle(new Obstacle(mTypes[type], *mTextures, getBattlefieldBounds));
        float leftBound = getBattlefieldBounds().left - getPosition().x;
        obstacle->move(leftBound, 0);
        // std::cout << "Spawing obstacle at " << getWorldPosition().y << '\n';
        attachChild(std::move(obstacle));
        mTimeToSpawn = mTimeBetweenSpawn;
    }
    else mTimeToSpawn -= dt;
}