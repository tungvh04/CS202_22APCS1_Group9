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
    };
}

#endif // CATEGORY_HPP