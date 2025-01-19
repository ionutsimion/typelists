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

    template <typename Type>
    [[nodiscard, maybe_unused]] decltype(auto) constexpr get_no_throw(size_t const, Type &&argument)
    {
        return std::forward<Type>(argument);
    }

    template <typename Head, typename ...TypeList>
    [[nodiscard]] decltype(auto) constexpr get_no_throw(size_t const index, Head &&first, TypeList &&...rest)
    {
        return index == 0ULL ? std::forward<Head>(first)
                             : get_no_throw(index - 1ULL, std::forward<TypeList>(rest)...);
    }

    template<typename ...TypeList>
    [[nodiscard]] decltype(auto) constexpr get(size_t const index, TypeList &&...arguments)
    {
        if (index >= sizeof...(TypeList))
            throw std::out_of_range("Index out of bounds");

        return get_no_throw<TypeList...>(index, std::forward<TypeList>(arguments)...);
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

    template<typename SearchedType, typename Type>
    [[nodiscard]] auto constexpr get_or_initialize(size_t const nth, [[maybe_unused]] SearchedType default_value, [[maybe_unused]] Type &&argument)
    {
        if constexpr (!std::is_same_v<Type, SearchedType>)
            return default_value;
        else
        {
            if (nth != 1ULL)
                return default_value;

            return std::forward<Type>(argument);
        }
    }

    template<typename SearchedType, typename Head, typename ...TypeList>
    [[nodiscard]] auto constexpr get_or_initialize(size_t const nth, SearchedType default_value, Head &&first, [[maybe_unused]] TypeList &&...rest)
    {
        if (nth > count<SearchedType, Head, TypeList...>())
            return default_value;

        if constexpr (std::is_same_v<Head, SearchedType>)
        {
            if (nth == 1ULL)
                return std::forward<Head>(first);

            return get_or_initialize<SearchedType, TypeList...>(nth - 1ULL, std::forward<SearchedType>(default_value), std::forward<TypeList>(rest)...);
        }
        else
            return get_or_initialize<SearchedType, TypeList...>(nth, std::forward<SearchedType>(default_value), std::forward<TypeList>(rest)...);
    }
}

#endif
