#include <SavingState.hpp>
#include <Utility.hpp>
#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <GameLevel.hpp>
#include <MapState.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


SavingState::SavingState(StateStack& stack, Context context)
: State(stack, context)
, mSavingText()
, mElapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mSavingText.setFont(font);
    mSavingText.setString("SAVING... \nPLEASE DON'T BREAK ANYTHING");
	mSavingText.setCharacterSize(100);
	centerOrigin(mSavingText);
	mSavingText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void SavingState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mSavingText);
}

bool SavingState::update(sf::Time dt)
{
	// Show state for 3 seconds, after return to menu
	gameLevel.save();
	mElapsedTime += dt;
	if (mElapsedTime > sf::seconds(3))
	{
		gameLevel.restart();
		requestStateClear();
		requestStackPush(States::Title);
	}
	return false;
}

bool SavingState::handleEvent(const sf::Event&)
{
	return false;
}