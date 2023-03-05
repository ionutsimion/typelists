#ifndef PITYPELISTS_TYPELIST_HXX
#define PITYPELISTS_TYPELIST_HXX

#include <tl_constants.hxx>
#include <tl_find.hxx>
#include <tl_matching_strategy.hxx>

namespace pi::tl
{
    /*!
     * @brief Counts the number of times SearchedType appears in the TypeList.
     * @tparam Strategy The matching strategy
     * @tparam SearchedType Type to count
     * @tparam TypeList Where to look in for SearchedType
     * @return The number of times SearchedType appears in TypeList, respecting the matching Strategy.
     */
    template <matching Strategy, typename SearchedType, typename ...TypeList>
    auto constexpr count()
    {
        return internal::count<apply_strategy_t<Strategy, SearchedType>, apply_strategy_t<Strategy, TypeList>...>();
    }

    /*!
     * @brief Counts the number of times SearchedType appears in the TypeList.
     * @tparam SearchedType Type to count
     * @tparam TypeList Where to look in for SearchedType
     * @return The number of times SearchedType appears in TypeList, using the relaxed matching strategy.
     */
    template <typename SearchedType, typename ...TypeList>
    auto constexpr count()
    {
        return count<matching::relaxed, SearchedType, TypeList...>();
    }

    /*!
     * @brief Index of a SearchedType in TypeList.
     * @tparam Strategy The matching strategy
     * @tparam SearchedType Type to count
     * @tparam TypeList Where to look in for SearchedType
     * @returns The 0-based index of SearchedType in TypeList, respecting the matching Strategy.
     */
    template <matching Strategy, typename SearchedType, typename ...TypeList>
    auto constexpr index_of()
    {
        return internal::find<apply_strategy_t<Strategy, SearchedType>, apply_strategy_t<Strategy, TypeList>...>();
    }

    /*!
     * @brief Index of a SearchedType in TypeList, using the relaxed matching strategy.
     * @tparam SearchedType Type to count
     * @tparam TypeList Where to look in for SearchedType
     * @returns The 0-based index of SearchedType in TypeList, using the relaxed matching strategy.
     */
    template <typename SearchedType, typename ...TypeList>
    auto constexpr index_of()
    {
        return index_of<matching::relaxed, SearchedType, TypeList...>();
    }
}

#endif
