#ifndef PITYPELISTS_TL_COUNT_HXX
#define PITYPELISTS_TL_COUNT_HXX

namespace pi::tl::internal
{
    template<typename SearchedType, typename Head, typename ...Tail>
    auto constexpr count()
    {
        return (std::is_same_v<SearchedType, Head> + ... + std::is_same_v<SearchedType, Tail>);
    }
}

#endif
