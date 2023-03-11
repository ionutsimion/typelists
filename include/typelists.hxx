#ifndef PITYPELISTS_TYPELISTS_HXX
#define PITYPELISTS_TYPELISTS_HXX

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
     * @returns The number of times SearchedType appears in TypeList, respecting the matching Strategy.
     */
    template <matching Strategy, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto consteval count();

    /*!
     * @brief Counts the number of times SearchedType appears in the TypeList, using the relaxed matching strategy.
     * @tparam SearchedType Type to count
     * @tparam TypeList Where to look in for SearchedType
     * @returns The number of times SearchedType appears in TypeList.
     */
    template <typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto consteval count();

    /*!
     * @brief Find the index of the Nth SearchedType in TypeList.
     * @tparam Strategy The matching strategy; default is relaxed
     * @tparam SearchedType Type to count
     * @tparam Nth The nth SearchedType in the TypeList
     * @tparam TypeList Where to look in for SearchedType
     * @returns The 0-based index of SearchedType in TypeList, respecting the matching Strategy.
     */
    template<matching Strategy, typename SearchedType, int64_t Nth, typename ...TypeList>
    [[nodiscard]] auto consteval find();

    /*!
     * @brief Find the index of the Nth SearchedType in TypeList, using relaxed matching strategy.
     * @tparam SearchedType Type to count
     * @tparam Nth The nth SearchedType in the TypeList
     * @tparam TypeList Where to look in for SearchedType
     * @returns The 0-based index of SearchedType in TypeList, respecting the matching Strategy.
     */
    template<typename SearchedType, int64_t Nth, typename ...TypeList>
    [[nodiscard]] auto consteval find();

    /*!
     * @brief Find the index of the first SearchedType in TypeList.
     * @tparam Strategy The matching strategy
     * @tparam SearchedType Type to count
     * @tparam TypeList Where to look in for SearchedType
     * @returns The 0-based index of SearchedType in TypeList, respecting the matching Strategy.
     */
    template <matching Strategy, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto consteval find();

    /*!
     * @brief Find the index of the first SearchedType in TypeList, using relaxed matching strategy.
     * @tparam SearchedType Type to count
     * @tparam TypeList Where to look in for SearchedType
     * @returns The 0-based index of SearchedType in TypeList, respecting the matching Strategy.
     */
    template <typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto consteval find();
}

namespace pi::tl
{
    template <matching Strategy, typename SearchedType, typename ...TypeList>
    auto consteval count()
    {
        return internal::count<apply_strategy_t<Strategy, SearchedType>, apply_strategy_t<Strategy, TypeList>...>();
    }

    template <typename SearchedType, typename ...TypeList>
    auto consteval count()
    {
        return count<matching::relaxed, SearchedType, TypeList...>();
    }

    template<matching Strategy, typename SearchedType, int64_t Nth, typename ...TypeList>
    auto consteval find()
    {
        return internal::find<apply_strategy_t<Strategy, SearchedType>, Nth, apply_strategy_t<Strategy, TypeList>...>();
    }

    template<typename SearchedType, int64_t Nth, typename ...TypeList>
    auto consteval find()
    {
        return find<matching::relaxed, SearchedType, Nth, TypeList...>();
    }

    template <matching Strategy, typename SearchedType, typename ...TypeList>
    auto consteval find()
    {
        return find<Strategy, SearchedType, 1, TypeList...>();
    }

    template <typename SearchedType, typename ...TypeList>
    auto consteval find()
    {
        return find<matching::relaxed, SearchedType, 1, TypeList...>();
    }
}

#endif
