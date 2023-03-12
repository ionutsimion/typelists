#include <catch2/catch_test_macros.hpp>

#include <typelists.hxx>
using namespace pi::tl;

namespace
{
    template <size_t I, typename ...TypeList>
    [[nodiscard]] decltype(auto) test_get([[maybe_unused]] TypeList &&...arguments)
    {
        return get<I>(std::forward<TypeList>(arguments)...);
    }

    template <matching Strategy, typename Default, typename ...TypeList>
    [[nodiscard]] auto test_get_or_initialize([[maybe_unused]] Default &&default_value, [[maybe_unused]] TypeList &&...arguments)
    {
        return get_or_initialize<Strategy, Default, TypeList...>(default_value, arguments...);
    }
}

SCENARIO("get")
{
    GIVEN("a type list with N arguments, N >= 1")
    {
        THEN("get<0> returns the first argument")
        {
            REQUIRE(test_get<0>(1, 2, 3, 4) == 1);
            REQUIRE(test_get<0>(true, 2.1, 3.1, '4') == true);
        }

        THEN("get<N-1> returns the last argument")
        {
            REQUIRE(test_get<0>(1) == 1);
            REQUIRE(test_get<1>(true, '4') == '4');
            REQUIRE(test_get<4>(10, 20, 30, 40, 50) == 50);
        }
    }
}

SCENARIO("get_or_initialize with strict matching strategy")
{
    GIVEN("a default value and a list of arguments")
    {
        THEN("get_or_initialize return the default value if there is no argument of the exact same type")
        {
            REQUIRE(test_get_or_initialize<matching::strict>(1) == 1);
        }

        THEN("get_or_initialize return the first argument of the same type, not the default")
        {
            int const i1 = 1;
            REQUIRE(test_get_or_initialize<matching::strict>(0, i1) == i1);
            //REQUIRE(test_get_or_initialize<matching::strict>(1, 3, 4) == 3);
        }
    }
}