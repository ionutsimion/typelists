#ifndef PITYPELISTS_TYPELISTS_HXX
#define PITYPELISTS_TYPELISTS_HXX

#include <tl_constants.hxx>
#include <tl_get.hxx>
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
     * @tparam Nth The 1-based instance of SearchedType in the TypeList
     * @tparam TypeList Where to look in for SearchedType
     * @returns The 0-based index of SearchedType in TypeList, respecting the matching Strategy.
     */
    template<matching Strategy, typename SearchedType, size_t Nth, typename ...TypeList>
    [[nodiscard]] auto consteval find_nth();

    /*!
     * @brief Find the index of the Nth SearchedType in TypeList, using relaxed matching strategy.
     * @tparam SearchedType Type to count
     * @tparam Nth The 1-based instance of SearchedType in the TypeList
     * @tparam TypeList Where to look in for SearchedType
     * @returns The 0-based index of SearchedType in TypeList, respecting the matching Strategy.
     */
    template<typename SearchedType, size_t Nth, typename ...TypeList>
    [[nodiscard]] auto consteval find_nth();

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

    /*!
     * @brief Get the argument at index Index in TypeList.
     * @tparam Index 0-based index (known at compile time)
     * @tparam TypeList List of types
     * @param arguments List of arguments
     * @return The argument at index Index in the arguments list.
     */
    template<size_t Index, typename ...TypeList>
    [[nodiscard]] decltype(auto) constexpr get(TypeList &&...arguments);

    /*!
     * @brief Tet the argument at the required index from the given TypeList
     * @tparam TypeList List of types
     * @param index 0-based index (not necessarily known at compile-time)
     * @param arguments List of arguments
     * @return The argument at the required index from the argument list.
     * @throws out_of_range if the index is larger than or equal to the number of arguments.
     * @note Due to a language limitation, the arguments must have compatible types (e.g. int, bool, double, char are allowed, but int, char * are not allowed)
     */
    template<typename ...TypeList>
    [[nodiscard]] decltype(auto) constexpr get(size_t index, TypeList &&...arguments);

    /*!
     * @brief Get the first argument of a certain type or the given default value, respecting the matching strategy.
     * @tparam Strategy The matching strategy
     * @tparam Nth The 1-based index of the argument of the SearchedType
     * @tparam SearchedType Type of the expected argument
     * @tparam TypeList List of types
     * @param default_value The fall-back initialization value in case there is no matching argument
     * @param arguments List of arguments
     * @return The first argument of the same type, respecting the matching strategy, or the default value.
     */
    template <matching Strategy, size_t Nth, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_nth_or_initialize(SearchedType default_value, TypeList &&...arguments);

    /*!
     * @brief Get the first argument of a certain type or the given default value, using relaxed strategy.
     * @tparam Nth The 1-based index of the argument of the SearchedType
     * @tparam SearchedType Type of the expected argument
     * @tparam TypeList List of types
     * @param default_value The fall-back initialization value in case there is no matching argument
     * @param arguments List of arguments
     * @return The first argument of the same type or the default value.
     */
    template <size_t Nth, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_nth_or_initialize(SearchedType default_value, TypeList &&...arguments);

    /*!
     * @brief Get the first argument of a certain type or the given default value, respecting the matching strategy.
     * @tparam Strategy The matching strategy
     * @tparam SearchedType Type of the expected argument
     * @tparam TypeList List of types
     * @param default_value The fall-back initialization value in case there is no matching argument
     * @param arguments List of arguments
     * @return The first argument of the same type, respecting the matching strategy, or the default value.
     */
    template <matching Strategy, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_or_initialize(SearchedType default_value, TypeList &&...arguments);

    /*!
     * @brief Get the first argument of a certain type or the given default value, using relaxed strategy.
     * @tparam SearchedType Type of the expected argument
     * @tparam TypeList List of types
     * @param default_value The fall-back initialization value in case there is no matching argument
     * @param arguments List of arguments
     * @return The first argument of the same type or the default value.
     */
    template <typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_or_initialize(SearchedType default_value, TypeList &&...arguments);
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

    template<matching Strategy, typename SearchedType, size_t Nth, typename ...TypeList>
    auto consteval find_nth()
    {
        return internal::find<apply_strategy_t<Strategy, SearchedType>, Nth, apply_strategy_t<Strategy, TypeList>...>();
    }

    template<typename SearchedType, size_t Nth, typename ...TypeList>
    auto consteval find_nth()
    {
        return find_nth<matching::relaxed, SearchedType, Nth, TypeList...>();
    }

    template <matching Strategy, typename SearchedType, typename ...TypeList>
    auto consteval find()
    {
        return find_nth<Strategy, SearchedType, 1, TypeList...>();
    }

    template <typename SearchedType, typename ...TypeList>
    auto consteval find()
    {
        return find_nth<matching::relaxed, SearchedType, 1, TypeList...>();
    }

    template<size_t Index, typename ...TypeList>
    [[nodiscard]] decltype(auto) constexpr get(TypeList &&...arguments)
    {
        return internal::get<Index, TypeList...>(std::forward<TypeList>(arguments)...);
    }

    template<typename ...TypeList>
    [[nodiscard]] decltype(auto) constexpr get(size_t index, TypeList &&...arguments)
    {
        return internal::get<TypeList...>(index, std::forward<TypeList>(arguments)...);
    }

    template <matching Strategy, size_t Nth, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_nth_or_initialize(SearchedType default_value, TypeList &&...arguments)
    {
        return internal::get_or_initialize<Nth, apply_strategy_t<Strategy, SearchedType>, apply_strategy_t<Strategy, TypeList>...>(
                apply_strategy_t<Strategy, SearchedType>(default_value)
              , apply_strategy_t<Strategy, TypeList>(arguments)...);
    }

    template <matching Strategy, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_nth_or_initialize(size_t const index, SearchedType default_value, TypeList &&...arguments)
    {
        return internal::get_or_initialize<apply_strategy_t<Strategy, SearchedType>, apply_strategy_t<Strategy, TypeList>...>(
                index
              , apply_strategy_t<Strategy, SearchedType>(default_value)
              , apply_strategy_t<Strategy, TypeList>(arguments)...);
    }

    template <size_t Nth, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_nth_or_initialize(SearchedType default_value, TypeList &&...arguments)
    {
        return get_nth_or_initialize<matching::relaxed, Nth, SearchedType, TypeList...>(
                std::forward<SearchedType>(default_value)
              , std::forward<TypeList>(arguments)...);
    }

    template <typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_nth_or_initialize(size_t const index, SearchedType default_value, TypeList &&...arguments)
    {
        return get_nth_or_initialize<matching::relaxed, SearchedType, TypeList...>(
                index
              , std::forward<SearchedType>(default_value)
              , std::forward<TypeList>(arguments)...);
    }

    template <matching Strategy, typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_or_initialize(SearchedType default_value, TypeList &&...arguments) {
        return get_nth_or_initialize<Strategy, 1LL, SearchedType, TypeList...>(
                std::forward<SearchedType>(default_value)
              , std::forward<TypeList>(arguments)...);
    }

    template <typename SearchedType, typename ...TypeList>
    [[nodiscard]] auto constexpr get_or_initialize(SearchedType default_value, TypeList &&...arguments)
    {
        return get_nth_or_initialize<matching::relaxed, 1LL, SearchedType, TypeList...>(
                std::forward<SearchedType>(default_value)
              , std::forward<TypeList>(arguments)...);
    }
}

#endif
