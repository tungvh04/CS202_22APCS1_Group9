#include <CountDownState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <cmath>

CountDown::CountDown(StateStack& stack, Context context)
    : State(stack, context)
    , mCountdownText()
    , mCountdownTime(sf::seconds(3))
    , mElapsedTime(sf::Time::Zero)
{
    sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f windowSize(context.window->getSize());

    mCountdownText.setFont(font);
    mCountdownText.setString("LOADING GAME...");
    mCountdownText.setCharacterSize(100);

    // Customize the appearance of the countdown text
    mCountdownText.setFillColor(sf::Color::White);
    centerOrigin(mCountdownText);
    mCountdownText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

bool CountDown::update(sf::Time dt)
{
    if (mCountdownTime > sf::Time::Zero)
    {
        mCountdownTime -= dt;
        updateCountdownUI();

        // If countdown reaches zero, start the game
        if (mCountdownTime <= sf::Time::Zero)
        {
            requestStackPop();
        }
    }
    else
    {
        // If countdown is done, return to menu after 3 seconds
        mElapsedTime += dt;
        if (mElapsedTime > sf::seconds(3))
        {
            requestStateClear();
            requestStackPush(States::Menu);
        }
    }

    return false;
}

void CountDown::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    // Create dark, semitransparent background
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mCountdownText);
}

bool CountDown::handleEvent(const sf::Event&)
{
    return false;
}

void CountDown::updateCountdownUI()
{
    // Calculate the remaining seconds in the countdown
    int seconds = static_cast<int>(std::ceil(mCountdownTime.asSeconds()));

    // Update the UI to display the countdown
    updateUIWithCountdown(seconds);
}

void CountDown::updateUIWithCountdown(int seconds)
{
    // Clear previous UI
    clearUI();

    // Display the countdown
    if (seconds > 0)
    {
        // Draw the countdown on the screen
        drawCountdownText(seconds);
    }
}

void CountDown::drawCountdownText(int seconds)
{
    // Set the text to display the countdown
    mCountdownText.setString(std::to_string(seconds));
    sf::RenderWindow& window = *getContext().window;
    // Draw the countdown text
    window.draw(mCountdownText);
}

void CountDown::clearUI()
{
    sf::RenderWindow& window = *getContext().window;
    window.clear();
}
