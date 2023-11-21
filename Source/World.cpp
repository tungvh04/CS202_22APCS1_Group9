#include <World.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow& window) : mWindow(window), mWorldView(window.getDefaultView()), mTextures(), mSceneGraph(), mSceneLayers(), mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f), mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f), mScrollSpeed(-50.f), mPlayerCharacter(nullptr) {
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt) {
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

    sf::Vector2f position = mPlayerCharacter->getPosition();
    sf::Vector2f velocity = mPlayerCharacter->getVelocity();

    if (position.x <= mWorldBounds.left + 150.f || position.x >= mWorldBounds.left + mWorldBounds.width - 150.f) {
        velocity.x = -velocity.x;
        mPlayerCharacter->setVelocity(velocity);
    }

    mSceneGraph.update(dt);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::loadTextures() {
    mTextures.load(Textures::Player, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Background, "Media/Textures/Desert.png");
}

void World::buildScene() {
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& texture = mTextures.get(Textures::Background);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    std::unique_ptr<Character> player(new Character(Character::Player, mTextures));
    mPlayerCharacter = player.get();
    mPlayerCharacter->setPosition(mSpawnPosition);
    mSceneLayers[Air]->attachChild(std::move(player));
}