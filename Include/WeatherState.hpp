#ifndef WEATHERSTATE_HPP
#define WEATHERSTATE_HPP

namespace Weather
{
    enum Type
    {
        Rain = 1 << 1,
        Snowing = 1 << 2,
    };
}

#endif //WEATHERSTATE_HPP