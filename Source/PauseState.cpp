#include <iostream>
#include <PauseState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <GameLevel.hpp>

PauseState::PauseState(StateStack& stack, Context context) : State(stack, context), mBackgroundSprite(), mPausedText(), mGUIContainer() {
    sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize();

    mPausedText.setFont(font);
    mPausedText.setString("Game Paused");
    mPausedText.setCharacterSize(70);
    centerOrigin(mPausedText);
    mPausedText.setPosition(0.5f * viewSize.x, 0.2f * viewSize.y);

    //Pause Menu
    auto continueButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	continueButton->setPosition(800, 300);
	continueButton->setText("Continue", 30);
	continueButton->setCallback([this] ()
	{
		requestStackPop();
	});
    auto restartButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    restartButton->setPosition(800, 400);
    restartButton->setText("Restart", 30);
    restartButton->setCallback([this]()
    {
        // requestStackPop();
        gameLevel.restart();
        requestStateClear();
        requestStackPush(States::Game);
    });
    auto settingButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    settingButton->setPosition(800, 500);
    settingButton->setText("Setting", 30);
    settingButton->setCallback([this]()
    {
        // requestStackPop();
        // Save later
        requestStateClear();
        requestStackPush(States::Menu);
        requestStackPush(States::Setting);
    });
    auto saveAndquitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    saveAndquitButton->setPosition(800, 600);
    saveAndquitButton->setText("Save and Quit", 30);
    saveAndquitButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::Saving);
    });
    auto menuButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    menuButton->setPosition(800, 700);
    menuButton->setText("Return to Main Menu", 30);
    menuButton->setCallback([this]()
    {
        gameLevel.save();
        requestStateClear();
        requestStackPush(States::Menu);
    });

    mGUIContainer.pack(continueButton);
    mGUIContainer.pack(restartButton);
    mGUIContainer.pack(settingButton);
    mGUIContainer.pack(saveAndquitButton);
    mGUIContainer.pack(menuButton);
    
    /*mInstructionText.setFont(font);
    mInstructionText.setString("(Press Backspace to return to the main menu)");
    centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * viewSize.x, 1.5f * viewSize.y);*/


}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mPausedText);
    window.draw(mGUIContainer);
}

bool PauseState::update(sf::Time) {
    return false;
}

bool PauseState::handleEvent(const sf::Event& event) {
    /*if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Escape) {
        // Escape pressed, remove itself to return to the game
        requestStackPop();
    }

    if (event.key.code == sf::Keyboard::BackSpace) {
        // Escape pressed, remove itself to return to the game
        requestStateClear();
        requestStackPush(States::Menu);
    }

    return false;*/
    mGUIContainer.handleEvent(event);
    return false;
}