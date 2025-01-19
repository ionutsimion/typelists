#ifndef PITYPELISTS_TL_COUNT_HXX
#define PITYPELISTS_TL_COUNT_HXX

namespace pi::tl::internal
{
    template <typename SearchedType>
    auto consteval count()
    {
        return 0ULL;
    }

    template<typename SearchedType, typename Head, typename ...Tail>
    auto consteval count()
    {
        return (static_cast<size_t>(std::is_same_v<SearchedType, Head>) + ... + static_cast<size_t>(std::is_same_v<SearchedType, Tail>));
    }
}

#endif
