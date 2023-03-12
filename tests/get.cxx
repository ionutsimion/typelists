#include <catch2/catch_test_macros.hpp>

#include <typelists.hxx>
using namespace pi::tl;

namespace
{
    template <size_t I, typename ...TypeList>
    decltype(auto) test_get_argument_of_type([[maybe_unused]] TypeList &&...arguments)
    {
        return get<I>(std::forward<TypeList>(arguments)...);
    }
}

SCENARIO("get")
{
    GIVEN("a type list with N arguments, N >= 1")
    {
        THEN("get<0> returns the first argument")
        {
            REQUIRE(test_get_argument_of_type<0>(1, 2, 3, 4) == 1);
            REQUIRE(test_get_argument_of_type<0>(true, 2.1, 3.1, '4') == true);
        }

        THEN("get<N-1> returns the last argument")
        {
            REQUIRE(test_get_argument_of_type<0>(1) == 1);
            REQUIRE(test_get_argument_of_type<1>(true, '4') == '4');
            REQUIRE(test_get_argument_of_type<4>(10, 20, 30, 40, 50) == 50);
        }
    }
}
