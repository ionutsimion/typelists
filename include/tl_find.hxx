#ifndef PITYPELISTS_TL_FIND_HXX
#define PITYPELISTS_TL_FIND_HXX

#include <type_traits>

#include <tl_constants.hxx>
#include <tl_count.hxx>

namespace pi::tl::internal
{
    template<typename SearchedType, int64_t Nth>
    auto constexpr find_no_assert()
    {
        return int64_t{ 0 };
    }

    template<typename SearchedType, int64_t Nth, typename Head, typename ...Tail>
    auto constexpr find_no_assert()
    {
        if constexpr (count<SearchedType, Head, Tail...>() < Nth)
            return npos;

        if constexpr (std::is_same_v<SearchedType, Head>)
        {
            if (Nth == 1)
                return int64_t{ 0 };
            else
                return find_no_assert<SearchedType, Nth - 1, Tail...>();
        }

        return int64_t{ 1 } + find_no_assert<SearchedType, Nth, Tail...>();
    }

    template <typename SearchedType, int64_t Nth, typename ...TypeList>
    auto constexpr find()
    {
        static_assert(sizeof...(TypeList) > 0U, "TypeList is expected to have at least on type.");
        static_assert(Nth > 0, "Nth is a 1-based index representing which 'instance' of SearchedType you want to find.");

        return find_no_assert<SearchedType, Nth, TypeList...>();
    }
}

#endif
