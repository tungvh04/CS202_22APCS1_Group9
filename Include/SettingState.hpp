#ifndef SETTINGSTATE_HPP
#define SETTINGSTATE_HPP

#include <State.hpp>
#include <Player.hpp>
#include <Container.hpp>
#include <Button.hpp>
#include <Label.h>
#include <MusicPlayer.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <array>

class SettingState : public State{
    public:
        SettingState(StateStack &stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        std::string fromKtoS(const sf::Keyboard::Key& key);
        void updateLabel();
        void addButtonLabel(Player::Action action, float y, const std::string& text, Context context);
        void settingSound();
	private:
		sf::Sprite mBackgroundSprite;
        sf::Sprite mSound1;
        sf::Sprite mSound2;
		GUI::Container mGUIContainer;
        GUI::Button mSoundButton;
		std::array<GUI::Button::Ptr, Player::ActionCount> mBindingButtons;
		std::array<GUI::Label::Ptr, Player::ActionCount> mBindingLabels;
        bool isSettingSound = false;
        float volume = 10;
        sf::CircleShape circle;
        sf::Text mVolume;
};
#endif