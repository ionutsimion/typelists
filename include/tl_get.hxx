#ifndef PITYPELISTS_TL_GET_HXX
#define PITYPELISTS_TL_GET_HXX

#include <tuple>

#include <tl_count.hxx>
#include <tl_find.hxx>

namespace pi::tl::internal
{
    template <size_t I, typename Head, typename ...Tail>
    [[nodiscard]] decltype(auto) constexpr get_no_assert(Head &&first, [[maybe_unused]] Tail &&...rest)
    {
        if constexpr (I == 0)
            return std::forward<Head>(first);
        else
            return get_no_assert<I - 1U, Tail...>(std::forward<Tail>(rest)...);
    }

    template <size_t I, typename ...TypeList>
    [[nodiscard]] decltype(auto) constexpr get(TypeList &&...arguments)
    {
        static_assert(sizeof...(TypeList), "TypeList is expected to have at least on type.");
        static_assert(I < sizeof...(TypeList), "Index out of bounds.");

        return get_no_assert<I, TypeList...>(std::forward<TypeList>(arguments)...);
    }

    template <typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_or_initialize([[maybe_unused]] SearchedType default_value, [[maybe_unused]] TypeList &&...arguments)
    {
        if constexpr (auto constexpr index = find<SearchedType, 1ULL, TypeList...>(); index == -1LL)
            return default_value;
        else
            return get<index, TypeList...>(std::forward<TypeList &&>(arguments)...);
    }
}

#endif
