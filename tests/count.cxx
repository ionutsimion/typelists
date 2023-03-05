#include <catch2/catch_test_macros.hpp>

#include <typelist.hxx>
using namespace pi::tl;

SCENARIO("count with strict matching strategy")
{
    GIVEN("a type, e.g. bool, it is not found in a list with several other types")
    {
        THEN("count<matching::strict, bool, int, char, float, unsigned>() returns 0")
        {
            REQUIRE(count<matching::strict, bool, int, char, float, unsigned>() == 0u);
        }
    }

    GIVEN("a type, e.g. int, it is found once in a list with several 'variations' of it: const, volatile, references")
    {
        THEN("count<matching::strict, int, int, int const, int volatile, int &, int const &, int &&>() returns 1")
        {
            REQUIRE(count<matching::strict, int, int, int const, int volatile, int &, int const &, int &&>() == 1u);
        }

        THEN("count<matching::strict, int, int const, int, int volatile, int &, int const &, int &&>() returns 1")
        {
            REQUIRE(count<matching::strict, int, int const, int, int volatile, int &, int const &, int &&>() == 1u);
        }

        THEN("count<matching::strict, int, int const, int volatile, int &, int const &, int &&, int>() returns 1")
        {
            REQUIRE(count<matching::strict, int, int const, int volatile, int &, int const &, int &&, int>() == 1u);
        }
    }

    GIVEN("a type, e.g. float, it is found as many times at it appears in a list with in which it appears at least twice")
    {
        THEN("count<matching::strict, float, float, float> return 2")
        {
            REQUIRE(count<matching::strict, float, float, float>() == 2u);
        }

        THEN("count<matching::strict, float, float, int, float> return 2")
        {
            REQUIRE(count<matching::strict, float, float, int, float>() == 2u);
        }

        THEN("count<matching::strict, float, int, float, float> return 2")
        {
            REQUIRE(count<matching::strict, float, int, float, float>() == 2u);
        }

        THEN("count<matching::strict, float, int, float, int, float> return 2")
        {
            REQUIRE(count<matching::strict, float, int, float, int, float>() == 2u);
        }

        THEN("count<matching::strict, float, int, float, int, float, int, float, int> return 3")
        {
            REQUIRE(count<matching::strict, float, int, float, int, float, int, float, int>() == 3u);
        }
    }
}
