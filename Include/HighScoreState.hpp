#ifndef HIGHSCORESTATE_HPP
#define HIGHSCORESTATE_HPP

#include <State.hpp>
#include <Player.hpp>
#include <Container.hpp>
#include <Button.hpp>
#include <Label.h>
#include <fstream>
#include <Const.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

class HighScoreState : public State{
    public:
        HighScoreState(StateStack &stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        void updateLabel();
        void addButtonLabel(Player::Action action, float y, const std::string& text, Context context);

        void loadScore();
	private:
		sf::Sprite mBackgroundSprite;
		GUI::Container mGUIContainer;
        std::array<std::pair<std::vector<float>, std::string>, 5> highScore;
};
#endif