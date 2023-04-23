#ifndef PITYPELISTS_TL_GET_HXX
#define PITYPELISTS_TL_GET_HXX

#include <tuple>

#include <tl_count.hxx>
#include <tl_find.hxx>

namespace pi::tl::internal
{
    template<size_t Index, typename Head, typename ...Tail>
    [[nodiscard]] decltype(auto) constexpr get_no_assert(Head &&first, [[maybe_unused]] Tail &&...rest)
    {
        if constexpr (Index == 0)
            return std::forward<Head>(first);
        else
            return get_no_assert<Index - 1U, Tail...>(std::forward<Tail>(rest)...);
    }

    template<size_t Index, typename ...TypeList>
    [[nodiscard]] decltype(auto) constexpr get(TypeList &&...arguments)
    {
        static_assert(Index < sizeof...(TypeList), "Index out of bounds.");

        return get_no_assert<Index, TypeList...>(std::forward<TypeList>(arguments)...);
    }

    template<size_t Nth, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_or_initialize([[maybe_unused]] SearchedType default_value, [[maybe_unused]] TypeList &&...arguments)
    {
        if constexpr (sizeof...(TypeList) == 0ULL)
            return default_value;
        else
        {
            auto constexpr index = find<SearchedType, Nth, TypeList...>();
            if constexpr (index == npos)
                return default_value;
            else
                return get<index, TypeList...>(std::forward<TypeList&&>(arguments)...);
        }
    }
}

#endif
