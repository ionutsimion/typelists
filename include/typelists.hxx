#ifndef PITYPELISTS_TYPELISTS_HXX
#define PITYPELISTS_TYPELISTS_HXX

#include <tl_constants.hxx>
#include <tl_find.hxx>
#include <tl_matching_strategy.hxx>

namespace pi::tl
{
    /*!
     * @brief Counts the number of times SearchedType appears in the TypeList.
     * @tparam [Optional] Strategy The matching strategy; default is relaxed
     * @tparam SearchedType Type to count
     * @tparam TypeList Where to look in for SearchedType
     * @returns The number of times SearchedType appears in TypeList, respecting the matching Strategy.
     */
    template <matching Strategy, typename SearchedType, typename ...TypeList>
    auto constexpr count();

    template <typename SearchedType, typename ...TypeList>
    auto constexpr count();

    /*!
     * @brief Index of a SearchedType in TypeList.
     * @tparam [Optional] Strategy The matching strategy; default is relaxed
     * @tparam SearchedType Type to count
     * @tparam [Optional] Nth The nth SearchedType in the TypeList; default is 1 (the first appearance)
     * @tparam TypeList Where to look in for SearchedType
     * @returns The 0-based index of SearchedType in TypeList, respecting the matching Strategy.
     */
    template<matching Strategy, typename SearchedType, int64_t Nth, typename ...TypeList>
    auto constexpr find();

    template<typename SearchedType, int64_t Nth, typename ...TypeList>
    auto constexpr find();

    template <matching Strategy, typename SearchedType, typename ...TypeList>
    auto constexpr find();

    template <typename SearchedType, typename ...TypeList>
    auto constexpr find();
}

namespace pi::tl
{
    template <matching Strategy, typename SearchedType, typename ...TypeList>
    auto constexpr count()
    {
        return internal::count<apply_strategy_t<Strategy, SearchedType>, apply_strategy_t<Strategy, TypeList>...>();
    }

    template <typename SearchedType, typename ...TypeList>
    auto constexpr count()
    {
        return count<matching::relaxed, SearchedType, TypeList...>();
    }

    template<matching Strategy, typename SearchedType, int64_t Nth, typename ...TypeList>
    auto constexpr find()
    {
        return internal::find<apply_strategy_t<Strategy, SearchedType>, Nth, apply_strategy_t<Strategy, TypeList>...>();
    }

    template<typename SearchedType, int64_t Nth, typename ...TypeList>
    auto constexpr find()
    {
        return find<SearchedType, Nth, TypeList...>();
    }

    template <matching Strategy, typename SearchedType, typename ...TypeList>
    auto constexpr find()
    {
        return find<Strategy, SearchedType, 1, TypeList...>();
    }

    template <typename SearchedType, typename ...TypeList>
    auto constexpr find()
    {
        return find<matching::relaxed, SearchedType, 1, TypeList...>();
    }
}

#endif
