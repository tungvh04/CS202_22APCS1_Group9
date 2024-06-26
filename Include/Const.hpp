#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <string>

#include <SFML/System/Time.hpp>

namespace Constants {
    constexpr static float playerSpeed = 600.f;
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

    constexpr static float trafficLightKillDelay = 0.1f;

    constexpr static float lightOffset = 900.f;
    constexpr static float lightOffsetLeft = 100.f;
    constexpr static float lightOffsetRight = 800.f;

    //Vehicle speed
    constexpr static float carSpeed = 150.f;
    constexpr static float trainSpeed = 1500.f;

    //Vehicle spawn cycle
    constexpr static float trainCycleTimeLowerBound = 6.f;
    constexpr static float trainCycleTimeUpperBound = 8.f;
    
    constexpr static float carCycleTimeLowerBound = 6.f;
    constexpr static float carCycleTimeUpperBound = 6.f;

    const std::string savePath = "Media/Save/Save.txt";
    const std::string saveMapPath = "Media/Save/";
    const std::string saveScorePath = "Media/Save/ScoreSave.txt";

    constexpr static float ScorePerSecond = 10.f;

    constexpr static float TemperatureSlope = 20000.f;
    constexpr static float SpeedSlope = 4000.f;

    constexpr static float freezeLimit = 0.f;
    constexpr static float burningLimit = 40.f;
    constexpr static float defaultTemperatureSpring = 16.f;
    constexpr static float defaultTemperatureAutumn = 5.f;
    constexpr static float defaultTemperatureWinter = -10.f;
    constexpr static float HotTemperatureShift = 20.f;
    constexpr static float ColdTemperatureShift = -20.f;

    constexpr static float FreezingDefaultSpeed = 0.3f;
    constexpr static float BurningDefaultSpeed = 0.8f;
    constexpr static float SpeedUpMult = 1.5f;
    constexpr static float SlowDownMult = 0.8f;

    constexpr static float characterHealth = 500.f;

    constexpr static float FreezingHealthDrainPerSecond = 50.f;
    constexpr static float BurningHealthDrainPerSecond = 20.f;

    constexpr static float healAmountLarge = 100.f;
    constexpr static float healAmountSmall = 50.f;
    constexpr static float hurtAmountLarge = 100.f;
    constexpr static float hurtAmountSmall = 50.f;

    constexpr static float MaxNumSaveScore = 1;
}

#endif // CONSTANTS_HPP
