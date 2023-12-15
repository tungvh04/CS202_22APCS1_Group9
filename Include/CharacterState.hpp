#ifndef CHARACTERSTATE_HPP
#define CHARACTERSTATE_HPP

#include <State.hpp>
#include <Player.hpp>
#include <Container.hpp>
#include <Button.hpp>
#include <Label.h>
#include <Animation.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <array>
class CharacterState : public State{
    public:
        CharacterState(StateStack &stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        void updateLabel(){};
        void addCharacterTexture(const std::string &nameCharacter, const std::string &color, int numOfPicture);
        void addBackGroudCharacterTexture(const std::string &nameCharacter, const std::string &color);
        void addButtonLabel(Player::Action action, float y, const std::string& text, Context context){};
	private:
        sf::Sprite mBackgroundSprite;
        sf::Sprite mCharacterSprite;
        sf::Sprite mBackgroundSpriteCharacter;

		GUI::Container mGUIContainer;
        std::vector<std::vector<sf::Texture>> mCharacterTexture;
        std::vector<sf::Texture> mBackgroundTextureCharacter;

        int typeCharacter = TypeCharacter::ID::RedDino;
        int currentFrame = 0;
        sf::Clock clock;
        sf::Time frameTime = sf::seconds(0.1f);
};
#endif