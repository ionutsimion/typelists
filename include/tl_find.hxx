#ifndef PITYPELISTS_TL_FIND_HXX
#define PITYPELISTS_TL_FIND_HXX

#include <type_traits>

#include <tl_constants.hxx>
#include <tl_count.hxx>

namespace pi::tl::internal
{
    template<typename SearchedType, typename Head, typename ...Tail>
    auto constexpr find_no_assert()
    {
        using result_t = decltype(npos);

        if constexpr (count<SearchedType, Head, Tail...>() == 0U)
            return npos;

        if constexpr (std::is_same_v<SearchedType, Head>)
            return result_t{ 0 };

        if constexpr (sizeof...(Tail) > 0U)
            return result_t{ 1 } + find_no_assert<SearchedType, Tail...>();
        else
            return result_t{ 1 };
    }

    template <typename SearchedType, typename ...TypeList>
    auto constexpr find()
    {
        static_assert(sizeof...(TypeList) > 0U, "TypeList is expected to have at least on type.");
        static_assert(count<SearchedType, TypeList...>() <= 1U, "SearchedType found more than once in the TypeList. Please use find_nth() function instead.");

        return find_no_assert<SearchedType, TypeList...>();
    }
}

#endif
