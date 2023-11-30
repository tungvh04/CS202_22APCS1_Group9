#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

namespace sf {
    class Texture;
    class Font;
}

namespace Textures {
    enum ID {
        Player,
        Background,
        TitleScreen,
        Title,
        Button,
        ButtonTouch,
        ButtonPressed,
        Cat,
        Cloud1,
        Cloud2,
        Cloud3,
    };
}

namespace Fonts {
    enum ID {
        Main,
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif // RESOURCEIDENTIFIERS_HPP