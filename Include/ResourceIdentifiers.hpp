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
        HighScore,
        Character,
        Map,
        Credit,
        Button,
        ButtonTouch,
        ButtonPressed,
        Cat,
        Cloud1,
        Cloud2,
        Cloud3,
        Key1,
        Key2,
        Grass,
        Sand,
        Ice,
        Car,
        Sound1,
        Sound2,
        Autumn,
        Spring,
        Winter,
        Road,
        Rail,
        Train,
        Island,
        Stone,
        TrafficLightRed,
        TrafficLightGreen,
        TrafficLightYellow,
        Death,
        Water,
        Raft,
        UpPlayer,
        LeftPlayer,
        RightPlayer,
    };
}
namespace SoundEffects {
    enum ID {
        Button,
        Step,
        Collison,
        SpringTheme,
        AutumnTheme,
        WinterTheme
    };
}
namespace Fonts {
    enum ID {
        Main,
    };
}
namespace TypeCharacter{
    enum ID {
        BlueDino,
        GreenDino,
        YellowDino,
        RedDino,
        BlueFrog,
        GreenFrog,
        YellowFrog,
        PinkFrog
    };
}
namespace TypeMap{
    enum ID {
        Spring,
        Autumn,
        Winter
    };
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		MissionTheme,
	};
}
// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif // RESOURCEIDENTIFIERS_HPP