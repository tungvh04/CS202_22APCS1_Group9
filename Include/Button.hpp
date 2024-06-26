#ifndef BOOK_BUTTON_HPP
#define BOOK_BUTTON_HPP

#include <Component.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>
#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>

class SoundPlayer;

namespace GUI
{
class Button : public Component
{
    public:
        typedef std::shared_ptr<Button> Ptr;
        typedef std::function<void()> Callback;

	public:
		Button(State::Context context);
        void setCallback(Callback callback);
        void setText(const std::string& text);
        void setText(const std::string&text, unsigned int sizeText);
        void setToggle(bool flag);

        virtual bool isSelectable() const;
        virtual void select();
        virtual void deselect();

        virtual void activate();
        virtual void deactivate();

        virtual void handleEvent(const sf::Event& event);


    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        Callback mCallback;
        const sf::Texture& mNormalTexture;
        const sf::Texture& mSelectedTexture;
        const sf::Texture& mPressedTexture;
        sf::Sprite mSprite;
        sf::Text mText;
        bool mIsToggle;
        SoundPlayer& mSounds;
};

}

#endif 