#include <MenuState.hpp>
#include <Utility.hpp>
#include <Foreach.hpp>
#include <ResourceHolder.hpp>
#include <Const.hpp>
#include <MovingObject.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack& stack, Context context) : State(stack, context), mGUIContainer() {
    sf::Texture& texture = context.textures->get(Textures::Background);
    mBackgroundSprite.setTexture(texture);
    mBackgroundSprite.scale(Constants::WindowWidth / mBackgroundSprite.getGlobalBounds().width, Constants::WindowHeight / mBackgroundSprite.getGlobalBounds().height);
    
    //Animation
    sf::Texture& cloudTexture_1 = context.textures->get(Textures::Cloud1);
    sf::Texture& cloudTexture_2 = context.textures->get(Textures::Cloud2);
    sf::Texture& cloudTexture_3 = context.textures->get(Textures::Cloud3);
    sf::Texture& catTexture = context.textures->get(Textures::Cat);
    sf::Texture& titleTexture = context.textures->get(Textures::Title);


    std::unique_ptr<MovingObject> cloud(new MovingObject(cloudTexture_1));
    cloud->setPosition(100, 50);
    cloud->setVelocity(150, 0);
    clouds.attachChild(std::move(cloud));
    
    std::unique_ptr<MovingObject> title(new MovingObject(titleTexture));
    title->setPosition(320, -50);
    title->setVelocity(0, 0);
    clouds.attachChild(std::move(title));

    std::unique_ptr<MovingObject> cloud_1(new MovingObject(cloudTexture_2));
    cloud_1->setPosition(1400, 350);
    cloud_1->setVelocity(200, 0);
    clouds.attachChild(std::move(cloud_1));

    std::unique_ptr<MovingObject> cloud_2(new MovingObject(cloudTexture_3));
    cloud_2->setPosition(0, 170);
    cloud_2->setVelocity(120, 0);
    clouds.attachChild(std::move(cloud_2));

    std::unique_ptr<MovingObject> cat(new MovingObject(catTexture));
    cat->setPosition(0, 1010);
    
    cat->setVelocity(100, 0);
    clouds.attachChild(std::move(cat));
    
    // A simple menu demonstration
    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition(800, 500);
	playButton->setText("Play", 40);
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::Character);
	});
    auto scoreButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    scoreButton->setPosition(800, 600);
    scoreButton->setText("High Score", 40);
    scoreButton->setCallback([this]()
    {
        requestStackPush(States::Score);
    });
    auto settingButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    settingButton->setPosition(800, 700);
    settingButton->setText("Setting", 40);
    settingButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Setting);
    });
    auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    exitButton->setPosition(800, 800);
    exitButton->setText("Exit", 40);
    exitButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Exit);
    });

    mGUIContainer.pack(playButton);
    mGUIContainer.pack(scoreButton);
    mGUIContainer.pack(settingButton);
    mGUIContainer.pack(exitButton);
}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mBackgroundSprite);
    window.draw(clouds);
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time dt) {
    clouds.update(dt);
    clouds.outOfScreen();
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return true;
}