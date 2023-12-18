#include <World.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

World::World(sf::RenderWindow& window) : mWindow(window), mWorldView(window.getDefaultView()), mTextures(), mSceneGraph(), mSceneLayers(), mWorldBounds(0.f, 0.f, /*mWorldView.getSize().x*/ 200000.f, 200000.f), mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f), mScrollSpeed(-50.f), mPlayerCharacter(nullptr) {
    loadTextures();
    buildScene();

    // tileManager.init();
    // tileManager.load();
    // tileManager.setCentre(mSpawnPosition);
    // tileManager.shiftY(Constants::initialShift);
    // tileManager.buildTillFull();
    sf::Vector2f gridspawn = mSpawnPosition;
    gridspawn.y += Constants::initialShift * Constants::GridSize;
    tileManager = TileManager(gridspawn);
    // Prepare the view
    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt) {

    //std::cout<<mPlayerCharacter->getPosition().x<<' '<<mPlayerCharacter->getPosition().y<<'\n';
    // Scroll the world, reset player velocity

    //sf::Vector2i currentPos=stateController.getIndex(mPlayerCharacter->getPosition());
    //std::cout<<currentPos.x<<' '<<currentPos.y<<'\n';

    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
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

    //Update Background depend on player position
    // tileManager.update(mPlayerCharacter->getPosition());
    tileManager.update(getBattlefieldBounds(), mTextures, dt);

    //std::cout<<mPlayerCharacter->getPosition().x<<" "<<mPlayerCharacter->getPosition().y<<" "<<'\n';
}

void World::draw() {
    mWindow.setView(mWorldView);
    // tileManager.draw(mWindow);
    mWindow.draw(tileManager);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue() {
    return mCommandQueue;
}

void World::loadTextures() {
    mTextures.load(Textures::Player, "Media/Textures/Eagle.png");
    //mTextures.load(Textures::Player, "Media/Textures/Tile/Tile"+toString(0)+".png");
    mTextures.load(Textures::Background, "Media/Textures/Desert.png");
    mTextures.load(Textures::Grass, "Media/Textures/Tile/Tile1.png");
    mTextures.load(Textures::Sand, "Media/Textures/Tile/Tile2.png");
    mTextures.load(Textures::Ice, "Media/Textures/Tile/Tile3.png");
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

    
    mOriginGrid = mSpawnPosition;

    //Making top left of grid origin
    //mOriginGrid.x-=Constants::GridSize*0.5f;
    //mOriginGrid.y-=Constants::GridSize*0.5f;

    //mOriginGrid.y-=Constants::GridSize*((Constants::TilesRenderedHeight+1)/2);
    //mOriginGrid.x-=Constants::GridSize*((Constants::TilesRenderedWide+1)/2);

    /*
    std::cout<<tileCnt<<'\n';
    
    for (int i=1;i<=Constants::TilesRenderedHeight;i++) {
        //Prepare grid
        int tmp=rand()%tileCnt;
        sf::Texture& texture = mTiles[tmp]->get(Textures::Background);
        //sf::IntRect textureRect(mOriginGrid.x,mOriginGrid.y,mOriginGrid.x+Constants::GridSize*(Constants::TilesRenderedWide),mOriginGrid.y+Constants::GridSize);
        sf::IntRect textureRect(mOriginGrid.x,mOriginGrid.y,mOriginGrid.x+Constants::GridSize,mOriginGrid.y+Constants::GridSize);
        //texture.setRepeated(true);
        
        std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
        backgroundSprite->setPosition(textureRect.left, textureRect.top);
        mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

        mOriginGrid.y+=Constants::GridSize;
    }
    */
    // Add player's character

    std::unique_ptr<Character> player(new Character(Character::Player, mTextures));
    mPlayerCharacter = player.get();
    mPlayerCharacter->setPosition(mSpawnPosition);
    mSceneLayers[Air]->attachChild(std::move(player));
}

void World::adaptPlayerPosition() {
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
    tileManager.checkNodeCollision(mPlayerCharacter->getBoundingRect(), playerCollidingNodes);
    // std::cout << "Player bounding rect: " << mPlayerCharacter->getBoundingRect().left << ' ' << mPlayerCharacter->getBoundingRect().top << ' ' << mPlayerCharacter->getBoundingRect().width << ' ' << mPlayerCharacter->getBoundingRect().height << '\n';
    // std::cout << "Number of colliding nodes: " << playerCollidingNodes.size() << '\n';
    for (auto node : playerCollidingNodes) {
        if (matchesCategories(node, Category::Grass)) {
            std::cout << "Colliding with grass\n";
        }
        else if (matchesCategories(node, Category::Ice)) {
            std::cout << "Colliding with ice\n";
        }
        else if (matchesCategories(node, Category::Sand)) {
            std::cout << "Colliding with sand\n";
        }
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
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}
