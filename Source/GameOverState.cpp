#include <GameOverState.hpp>
#include <Utility.hpp>
#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <GameLevel.hpp>
#include <MusicPlayer.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mGameOverText()
, mElapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mGameOverText.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionFailure)
		mGameOverText.setString("GAME OVER");

	mGameOverText.setCharacterSize(100);
	centerOrigin(mGameOverText);
	mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	context.music->play(Music::GameOverTheme);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	// Show state for 3 seconds, after return to menu
	mElapsedTime += dt;
	if (mElapsedTime > sf::seconds(3))
	{
		gameLevel.restart();
		requestStateClear();
		requestStackPush(States::Menu);
	}
	return false;
}

bool GameOverState::handleEvent(const sf::Event&)
{
	return false;
}