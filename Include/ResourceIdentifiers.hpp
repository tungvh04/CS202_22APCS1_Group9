#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

namespace sf {
    class Texture;
    class Font;
    class SoundBuffer;
}

namespace Textures {
    enum ID {
        Player,
        Background,
        TitleScreen,
        Title,
        HighScore,
        Character,
        Countdown,
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
        Oto,
        Oto1,
        Oto2,
        Sound1,
        Sound2,
        Autumn,
        Spring,
        Winter,
        Atlantis,
        Soil,
        Road,
        Rail,
        Train,
        Island,
        Stone,
        TrafficLightRed,
        TrafficLightGreen,
        TrafficLightYellow,
        Water,
        Raft,
        BlueDino,
        GreenDino,
        YellowDino,
        RedDino,
        BlueFrog,
        GreenFrog,
        YellowFrog,
        PinkFrog,
        BlueDinoDeath,
        GreenDinoDeath,
        YellowDinoDeath,
        RedDinoDeath,
        BlueFrogDeath,
        GreenFrogDeath,
        YellowFrogDeath,
        PinkFrogDeath,
        SlowDown,
        SpeedUp,
        Freezing,
        IceCream,
        Burning,
        Tree,
        Tree1,
        Tree2,
        Tree3,
        Tree4,
        Tree5,
        Log,
        Raining,
        Snowing,
    };
}
namespace SoundEffects {
    enum ID {
        Button
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
        Winter,
        Atlantis,
    };
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		MissionTheme,
        GameOverTheme,
        CountDownTheme
	};
}
// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffects::ID> SoundBufferHolder;

#endif // RESOURCEIDENTIFIERS_HPP