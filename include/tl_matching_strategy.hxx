#ifndef PITYPELISTS_TL_MATCHING_STRATEGY_HXX
#define PITYPELISTS_TL_MATCHING_STRATEGY_HXX

#include <type_traits>

namespace pi::tl
{
    /*! The matching strategy is used to select how the matching/searching is done. */
    enum class matching
    {
        relaxed /*! matches types without or with different modifiers, references with non-references */
      , strict  /*! matches types only if they are an exact match: same modifiers, same type of reference */
    };

    template <matching Strategy, typename Type>
    using apply_strategy_t = std::conditional_t<Strategy == matching::relaxed, std::decay_t<Type>, Type>;
}

#endif
