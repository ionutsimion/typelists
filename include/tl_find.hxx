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

        if constexpr (count<SearchedType, Head, Tail...>() == 0u)
            return npos;

        if constexpr (std::is_same_v<SearchedType, Head>)
            return result_t{ 0 };

        if constexpr (sizeof...(Tail) > 0u)
            return result_t{ 1 } + find_no_assert<SearchedType, Tail...>();
        else
            return result_t{ 1 };
    }

    template <typename SearchedType, typename ...TypeList>
    auto constexpr find()
    {
        static_assert(sizeof...(TypeList) > 0u, "TypeList is expected to have at least on type.");

        return find_no_assert<SearchedType, TypeList...>();
    }
}

#endif
