#ifndef PITYPELISTS_TL_FIND_HXX
#define PITYPELISTS_TL_FIND_HXX

#include <type_traits>

#include <tl_constants.hxx>
#include <tl_count.hxx>

namespace pi::tl::internal
{
    template <typename SearchedType, size_t Nth>
    auto consteval find_no_assert()
    {
        return int64_t{ 0 };
    }

    template <typename SearchedType, size_t Nth, typename Head, typename ...Tail>
    auto consteval find_no_assert()
    {
        if constexpr (count<SearchedType, Head, Tail...>() < Nth)
            return npos;

        if constexpr (std::is_same_v<SearchedType, Head>)
        {
            if constexpr (Nth == 1U)
                return int64_t{ 0 };
            else
				return int64_t{ 1 } + find_no_assert<SearchedType, Nth - 1U, Tail...>();
        }
        else
			return int64_t{ 1 } + find_no_assert<SearchedType, Nth, Tail...>();
    }

    template <typename SearchedType, size_t Nth, typename ...TypeList>
    auto consteval find()
    {
        static_assert(sizeof...(TypeList) > 0U, "TypeList is expected to have at least on type.");
        static_assert(Nth > 0U, "Nth is a 1-based index representing which 'instance' of SearchedType you want to find.");

        return find_no_assert<SearchedType, Nth, TypeList...>();
    }
}

#endif
