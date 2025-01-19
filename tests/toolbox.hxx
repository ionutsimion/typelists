#ifndef PITYPELISTS_TOOLBOX_HXX
#define PITYPELISTS_TOOLBOX_HXX

#include <cmath>

namespace pi
{
    template<typename Type> auto constexpr zero = Type{ 0 };
    template<typename Type> auto constexpr one = Type{ 1 };

    template<std::floating_point Type>
    auto constexpr epsilon = std::numeric_limits<Type>::epsilon();
}

#endif //PITYPELISTS_TOOLBOX_HXX
