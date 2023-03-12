#ifndef PITYPELISTS_TL_GET_HXX
#define PITYPELISTS_TL_GET_HXX

#include <tuple>

#include <tl_count.hxx>
#include <tl_find.hxx>

namespace pi::tl::internal
{
    template <typename SearchedType, typename Head, typename ...Tail>
    [[nodiscard]] decltype(auto) constexpr get_no_assert(Head &&first, [[maybe_unused]] Tail &&...rest)
    {
        if constexpr (std::is_same_v<SearchedType, Head>)
            return std::forward<Head>(first);
        else
            return get_no_assert<SearchedType, Tail...>(std::forward<Tail>(rest)...);
    }

    template <typename SearchedType, typename ...TypeList>
    [[nodiscard]] decltype(auto) constexpr get([[maybe_unused]] TypeList &&...arguments)
    {
        static_assert(sizeof...(TypeList) > 0U, "TypeList is expected to have at least on type.");
        static_assert(count<SearchedType, TypeList...>() >= 1U, "There is no argument of type SearchedType.");

        return get_no_assert<SearchedType, TypeList...>(std::forward<TypeList>(arguments)...);
    }
}

#endif
