#include <GameState.hpp>

#include <GameLevel.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

GameState::GameState(StateStack& stack, Context context) : State(stack, context), mWorld(*context.window), mPlayer(*context.player) 
{
    mPlayer.setMissionStatus(Player::MissionRunning);

    mLevelText.setFont(context.fonts->get(Fonts::Main));
    mLevelText.setPosition(5.f, 20.f);
    mLevelText.setCharacterSize(50);
    // mLevelText.setString("Level: " + std::to_string(gameLevel.getLevel()));
}

void GameState::draw() {
    mWorld.draw();
    sf::RenderWindow& mWindow = *getContext().window;
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mLevelText);
    // std::cout << "Drawn level: " << gameLevel.getLevel() << std::endl;
    // std::cout << "String = " << mLevelText.getString().toAnsiString() << std::endl;
}

bool GameState::update(sf::Time dt) {
    mWorld.update(dt);

    if (!mWorld.hasAlivePlayer())
	{
		mPlayer.setMissionStatus(Player::MissionFailure);
		requestStackPush(States::GameOver);
	}
	/*else if (mWorld.hasPlayerReachedEnd())
	{
		mPlayer.setMissionStatus(Player::MissionSuccess);
		requestStackPush(States::GameOver);
	}*/

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);

    // int level = gameLevel.getLevel();
    // std::string levelString = "Level: " + std::to_string(level);
    int level = gameLevel.getScore();
    std::string levelString = "Score: " + std::to_string(level);
    mLevelText.setString(levelString);

    return true;
}

bool GameState::handleEvent(const sf::Event& event) {
    // Game input handling
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::Pause);

    return true;
}