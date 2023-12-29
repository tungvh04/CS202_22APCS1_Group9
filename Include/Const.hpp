#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <string>

namespace Constants {
    constexpr static float playerSpeed = 500.f;
    constexpr static float GridSize = 80.f;
    constexpr static float scrollSpeed = -100.f;
    constexpr static float BorderDistance = 40.f;
    constexpr static int TilesRenderedHeight = 25;
    constexpr static int TilesRenderedWide = 30;
    constexpr static int SwapRowWhenLower = 10;
    constexpr static int initialShift = 15;
    const std::string vehiclePath = "Media/Textures/Vehicle/";
    constexpr static float WindowHeight = 1080;
    constexpr static float WindowWidth = 1920;
    constexpr static float battlefieldBoundsHeightOffset = 800.f;
    constexpr static float battlefieldBoundsWidthOffset = 800.f;

    //Vehicle speed
    constexpr static float carSpeed = 150.f;
    constexpr static float trainSpeed = 1500.f;
}

#endif // CONSTANTS_HPP
