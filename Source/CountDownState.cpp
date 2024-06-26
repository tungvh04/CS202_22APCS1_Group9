#include <CountDownState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>
#include <MusicPlayer.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <cmath>

CountDownState::CountDownState(StateStack& stack, Context context)
    : State(stack, context)
    , mCountdownText()
    , mCountdownTime(sf::seconds(4))
    , mElapsedTime(sf::Time::Zero)
{
    mBackground.setTexture(context.textures->get(Textures::Countdown));

    sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f windowSize(context.window->getSize());

    mCountdownText.setFont(font);
    mCountdownText.setCharacterSize(200);

    // Customize the appearance of the countdown text
    mCountdownText.setFillColor(sf::Color::White);
    centerOrigin(mCountdownText);
    mCountdownText.setPosition(0.48f * windowSize.x, 0.35f * windowSize.y);

    context.music->play(Music::CountDownTheme);
}

bool CountDownState::update(sf::Time dt)
{
    if (mCountdownTime > sf::Time::Zero)
    {
        mCountdownTime -= dt;
        updateCountdownUI();

        // If countdown reaches zero, start the game
        if (mCountdownTime <= sf::Time::Zero)
        {
            requestStackPop();
            requestStackPush(States::Game);
        }
    }

    return false;
}

void CountDownState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());


    window.draw(mBackground);
    window.draw(mCountdownText);
}

bool CountDownState::handleEvent(const sf::Event&)
{
    return false;
}

void CountDownState::updateCountdownUI()
{
    // Calculate the remaining seconds in the countdown
    int seconds = static_cast<int>(std::ceil(mCountdownTime.asSeconds()));

    // Update the UI to display the countdown
    updateUIWithCountdown(seconds);
}

void CountDownState::updateUIWithCountdown(int seconds)
{
    // Clear previous UI
    clearUI();

    // Display the countdown
    if (seconds > 1)
    {
        // Draw the countdown on the screen
        drawCountdownText(seconds);
    }
    else
    {
        //Signal the start
        updateUIForGo();
    }
}

void CountDownState::drawCountdownText(int seconds)
{
    // Set the text to display the countdown
    mCountdownText.setString(std::to_string(seconds-1));
    
    // Draw the countdown text
    sf::RenderWindow& window = *getContext().window;
    window.draw(mCountdownText);
}

void CountDownState::clearUI()
{
    sf::RenderWindow& window = *getContext().window;
    window.clear();
}

void CountDownState::updateUIForGo()
{
    mCountdownText.setString("GO");
    centerOrigin(mCountdownText);

    sf::Vector2f windowSize = getContext().window->getView().getSize();

    mCountdownText.setPosition(0.5f * windowSize.x, 0.48f * windowSize.y);

    sf::RenderWindow& window = *getContext().window;
    window.draw(mCountdownText);
}