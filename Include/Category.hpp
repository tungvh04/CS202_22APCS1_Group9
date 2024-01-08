#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category
{
    enum Type
    {
        None = 0,
        Scene = 1 << 0,
        PlayerCharacter = 1 << 1,
        Object = 1 << 2,
        Tile = 1 << 3,
        Grass = 1 << 4,
        Sand = 1 << 5,
        Ice = 1 << 6,
        Road = 1 << 7,
        Obstacle = 1 << 8,
        Car = 1 << 9,
        Rail = 1 << 10,
        Stone = 1 << 11,
        Island = 1 << 12,
        TrafficLightRed = 1 << 13,
        TrafficLightGreen = 1 << 14,
        TrafficLightYellow = 1 << 15,
        SlowDown = 1 << 16,
        SpeedUp = 1<< 17,
        Cold = 1 << 18,
        Hot = 1 << 19,
        PickUp = 1 << 20,
        Soil = 1 << 21,
        HealSmall = 1 << 22,
        HealLarge = 1 << 23,
        HurtSmall = 1 << 24,
        HurtLarge = 1 << 25,
    };
}

#endif // CATEGORY_HPP