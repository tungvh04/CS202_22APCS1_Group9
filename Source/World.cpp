#include <World.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

#include <GameLevel.hpp>

World::World(sf::RenderWindow& window) : mWindow(window), mWorldView(window.getDefaultView()), mTextures(), mSceneGraph(), mSceneLayers(), mWorldBounds(0.f, 0.f, /*mWorldView.getSize().x*/ 200000.f, 200000.f), mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f), mScrollSpeed(Constants::scrollSpeed), mPlayerCharacter(nullptr) {
    loadTextures();
    buildScene();

    // Prepare the view
    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt) {

    //std::cout<<mPlayerCharacter->getPosition().x<<' '<<mPlayerCharacter->getPosition().y<<'\n';
    // Scroll the world, reset player velocity

    //sf::Vector2i currentPos=stateController.getIndex(mPlayerCharacter->getPosition());
    //std::cout<<currentPos.x<<' '<<currentPos.y<<'\n';

    if (!mPlayerCharacter->isDestroyed()) mWorldView.move(0.f, mScrollSpeed * dt.asSeconds() * gameLevel.getSpeedMultiplier());
    mPlayerCharacter->setVelocity(0.f, 0.f);

    // Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }
    adaptPlayerVelocity();

    handleCollisions();

    // Regular update step, adapt position (correct if outside view)
    mSceneGraph.update(dt);
    adaptPlayerPosition();

    // Update level
    gameLevel.incrementScore(dt.asSeconds() * Constants::ScorePerSecond);

}

void World::draw() { 
    mWindow.setView(mWorldView);
    // tileManager.draw(mWindow);
    // mWindow.draw(tileManager);
    // mWindow.draw(mTileManager);
    mWindow.draw(mSceneGraph);
    //std::cout<<"Here\n";
    if (mPlayerCharacter->isFreezing()) {
        sf::Sprite overlay(mTextures.get(Textures::ID::Freezing));
        overlay.setPosition(0,0);
        mWindow.setView(mWindow.getDefaultView());
        mWindow.draw(overlay);
    }
    //mWindow.setView();

}

CommandQueue& World::getCommandQueue() {
    return mCommandQueue;
}

bool World::hasAlivePlayer() const
{
	return !mPlayerCharacter->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const
{
	return !mWorldBounds.contains(mPlayerCharacter->getPosition());
}

void World::loadTextures() {
    
    mTextures.load(Textures::Player, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Background, "Media/Textures/Desert.png");
    mTextures.load(Textures::Grass, "Media/Textures/Tile/Tile1.png");
    mTextures.load(Textures::Sand, "Media/Textures/Tile/Tile2.png");
    mTextures.load(Textures::Ice, "Media/Textures/Vehicle/Raft.png");
    mTextures.load(Textures::Car, "Media/Textures/Vehicle/Truck.png");
    mTextures.load(Textures::Road, "Media/Textures/Tile/Tile4.png");
    mTextures.load(Textures::Rail, "Media/Textures/Tile/Rail.png");
    mTextures.load(Textures::Train, "Media/Textures/Vehicle/Train.png");
    mTextures.load(Textures::Island, "Media/Textures/Tile/Tile5.png");
    mTextures.load(Textures::Stone, "Media/Textures/Vehicle/Stone.png");
    mTextures.load(Textures::TrafficLightGreen, "Media/Textures/TrafficLightGreen.png");
    mTextures.load(Textures::TrafficLightRed, "Media/Textures/TrafficLightRed.png");
    mTextures.load(Textures::TrafficLightYellow, "Media/Textures/TrafficLightYellow.png");
    mTextures.load(Textures::Death, "Media/Textures/death.png");
    mTextures.load(Textures::UpPlayer, "Media/Textures/moveUp.png");

    mTextures.load(Textures::BlueDino, "Media/Textures/Characters/Moving/BlueDino.png");
    mTextures.load(Textures::RedDino, "Media/Textures/Characters/Moving/RedDino.png");
    mTextures.load(Textures::GreenDino, "Media/Textures/Characters/Moving/GreenDino.png");
    mTextures.load(Textures::YellowDino, "Media/Textures/Characters/Moving/YellowDino.png");

    mTextures.load(Textures::BlueFrog, "Media/Textures/Characters/Moving/BlueFrog.png");
    mTextures.load(Textures::GreenFrog, "Media/Textures/Characters/Moving/GreenFrog.png");
    mTextures.load(Textures::PinkFrog, "Media/Textures/Characters/Moving/PinkFrog.png");
    mTextures.load(Textures::YellowFrog, "Media/Textures/Characters/Moving/YellowFrog.png");

    mTextures.load(Textures::BlueDinoDeath, "Media/Textures/Characters/Death/BlueDino.png");
    mTextures.load(Textures::RedDinoDeath, "Media/Textures/Characters/Death/RedDino.png");
    mTextures.load(Textures::GreenDinoDeath, "Media/Textures/Characters/Death/GreenDino.png");
    mTextures.load(Textures::YellowDinoDeath, "Media/Textures/Characters/Death/YellowDino.png");

    mTextures.load(Textures::BlueFrogDeath, "Media/Textures/Characters/Death/BlueFrog.png");
    mTextures.load(Textures::GreenFrogDeath, "Media/Textures/Characters/Death/GreenFrog.png");
    mTextures.load(Textures::PinkFrogDeath, "Media/Textures/Characters/Death/PinkFrog.png");
    mTextures.load(Textures::YellowFrogDeath, "Media/Textures/Characters/Death/YellowFrog.png");
    mTextures.load(Textures::SpeedUp, "Media/Textures/SpeedUp.png");
    mTextures.load(Textures::SlowDown, "Media/Textures/SlowDown.png");
    mTextures.load(Textures::Freezing, "Media/Textures/freezeScreenOverlay.png");
}

void World::buildScene() {
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    /*
    // Prepare the tiled background
    sf::Texture& texture = mTextures.get(Textures::Background);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    
    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
    */

    // Grid making

    // sf::Vector2f gridspawn = mSpawnPosition;
    // gridspawn.y += Constants::initialShift * Constants::GridSize;
    // SceneNode::Ptr grid(new TileManager(gridspawn, std::bind(&World::getBattlefieldBounds, this), &mTextures));
    // mSceneLayers[Background]->attachChild(std::move(grid));


    sf::Vector2f gridspawn = mSpawnPosition;
    gridspawn.y += Constants::initialShift * Constants::GridSize;
    // SceneNode::Ptr grid(GameObject(gridspawn, std::bind(&World::getBattlefieldBounds, this), &mTextures));
    SceneNode::Ptr grid(new GameObject(gridspawn, std::bind(&World::getBattlefieldBounds, this), &mTextures));
    mSceneLayers[Background]->attachChild(std::move(grid));
    
    mOriginGrid = mSpawnPosition;
    // Add player's character

    std::unique_ptr<Character> player(new Character(Character::Player, mTextures));
    mPlayerCharacter = player.get();
    mPlayerCharacter->setPosition(mSpawnPosition);
    mPlayerCharacter->setDefaultTemperature(Constants::defaultTemperatureSpring);
    mSceneLayers[Air]->attachChild(std::move(player));

    mPlayerCharacter->setWorldSceneGraph(&mSceneGraph);
}

void World::adaptPlayerPosition() {
    if (!mPlayerCharacter->getBoundingRect().intersects(getViewBounds())) {
        Command command;
        command.category = Category::PlayerCharacter;
        command.action = derivedAction<Character>([](Character& c, sf::Time) { c.destroy(); });
        CommandQueue& commands = getCommandQueue();
        commands.push(command);
        return;
    }
    return;
    // Keep player's position inside the screen bounds, at least borderDistance units from the border
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
    const float borderDistance = Constants::BorderDistance;

    sf::Vector2f position = mPlayerCharacter->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
    mPlayerCharacter->setPosition(position);
}

void World::adaptPlayerVelocity() {
    return;
    sf::Vector2f velocity = mPlayerCharacter->getVelocity();

    // If moving diagonally, reduce velocity (to have always same velocity)
    if (velocity.x != 0.f && velocity.y != 0.f) {
        mPlayerCharacter->setVelocity(velocity / std::sqrt(2.f));
    }

    // Add scrolling velocity
    // mPlayerCharacter->accelerate(0.f, mScrollSpeed);
}

bool matchesCategories(SceneNode* node, Category::Type type) {
    return (node->getCategory() & type) != 0;
}

void World::handleCollisions() {
    std::set<SceneNode*> playerCollidingNodes;
    mSceneGraph.checkNodeCollision(mPlayerCharacter->getBoundingRect(), playerCollidingNodes);
    // mTileManager.checkNodeCollision(mPlayerCharacter->getBoundingRect(), playerCollidingNodes);
    // std::cout << "Player bounding rect: " << mPlayerCharacter->getBoundingRect().left << ' ' << mPlayerCharacter->getBoundingRect().top << ' ' << mPlayerCharacter->getBoundingRect().width << ' ' << mPlayerCharacter->getBoundingRect().height << '\n';
    // std::cout << "Number of colliding nodes: " << playerCollidingNodes.size() << '\n';
    for (auto node : playerCollidingNodes) {
        if (matchesCategories(node, Category::Obstacle)) {
            //std::cout << "Colliding with obstacle\n";
            Command command;
            command.category = Category::PlayerCharacter;
            command.action = derivedAction<Character>([](Character& c, sf::Time) { c.destroy(); });
            mCommandQueue.push(command);
        }
        if (matchesCategories(node, Category::Hot)) {
            mPlayerCharacter->shiftTemperature(Constants::HotTemperatureShift);
        }
        if (matchesCategories(node, Category::Cold)) {
            mPlayerCharacter->shiftTemperature(Constants::ColdTemperatureShift);
        }
        /*
        if (matchesCategories(node, Category::Ice)) {
            // setWater()
        }
        if (matchesCategories(node, Category::Island)) {
            // setIsland()
        }
        if (matchesCategories(node, Category::Ice)) {
            // setWater()
        }
        if (matchesCategories(node, Category::Island)) {
            // setIsland()
        }
        */
        if (matchesCategories(node, Category::SpeedUp)) {
            speedUp();
        }
        if (matchesCategories(node, Category::SlowDown)) {
            slowDown();
        }
        if (matchesCategories(node, Category::PickUp)) {
            node->setDestroy();
        }
        // if (matchesCategories(node, Category::Car)) {
            // std::cout << "Colliding with car\n";
        // }
        // if (matchesCategories(node, Category::Grass)) {
            // std::cout << "Colliding with grass\n";
        // }
        // else if (matchesCategories(node, Category::Ice)) {
            // std::cout << "Colliding with ice\n";
        // }
        // else if (matchesCategories(node, Category::Sand)) {
            // std::cout << "Colliding with sand\n";
        // }
    }
}
sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}
sf::FloatRect World::getBattlefieldBounds() const
{
	// Return view bounds + some area at top, where enemies spawn
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= Constants::battlefieldBoundsHeightOffset;
	bounds.height += Constants::battlefieldBoundsHeightOffset*2;
    bounds.left -= Constants::battlefieldBoundsWidthOffset;
	bounds.width += Constants::battlefieldBoundsWidthOffset*2;

	return bounds;
}

void World::speedUp() {
    //std::cout<<"Speeding ticket\n";
    //mPlayerCharacter->setVelocity(mPlayerCharacter->getVelocity()*2.f);
    mPlayerCharacter->setSpeedMult(2.f);
}

void World::slowDown() {
    //std::cout<<"Un-Speeding ticket\n";
    //mPlayerCharacter->setVelocity(mPlayerCharacter->getVelocity()*0.5f);
    mPlayerCharacter->setSpeedMult(0.8f);
}
