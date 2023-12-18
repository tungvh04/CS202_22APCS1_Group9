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
    };
}

#endif // CATEGORY_HPP