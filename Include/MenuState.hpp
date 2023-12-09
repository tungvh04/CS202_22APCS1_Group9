#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <State.hpp>
#include <SceneNode.hpp>
#include <Container.hpp>
#include <Button.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
public:
    MenuState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

    void updateOptionText();

private:
    enum OptionNames {
        Play,
        Exit,
    };

private:
    sf::Sprite mBackgroundSprite;
    GUI::Container mGUIContainer;
    SceneNode clouds; 
    
};

#endif // MENUSTATE_HPP