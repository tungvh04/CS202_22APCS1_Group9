#ifndef COUNTDOWNSTATE_HPP
#define COUNTDOWNSTATE_HPP

#include <State.hpp>
#include <Container.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class CountDown : public State
{
public:
    CountDown(StateStack& stack, Context context);
    bool update(sf::Time dt) override;
    void draw() override;
    bool handleEvent(const sf::Event&) override;

private:
    void updateCountdownUI();
    void updateUIWithCountdown(int seconds);
    void drawCountdownText(int seconds);
    void clearUI();

private:
    sf::Text mCountdownText;
    sf::Time mCountdownTime;
    sf::Time mElapsedTime;
};

#endif // COUNTDOWNSTATE_HPP
