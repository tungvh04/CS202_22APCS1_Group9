#ifndef MAP_HPP
#define MAP_HPP

#include <State.hpp>
#include <Entity.hpp>
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
class MapState : public State, Entity{
    public:
        MapState(StateStack &stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        sf::Sprite mBackgroundSprite;
        sf::Sprite mMap;
        std::array<sf::Texture, 4> listMap;
        GUI::Container mGUIContainer;
        int typeMap = TypeMap::ID::Spring;
};
extern TypeMap::ID typeOfMap;
#endif