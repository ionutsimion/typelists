#include <catch2/catch_test_macros.hpp>

#include <typelists.hxx>
using namespace pi::tl;

SCENARIO("count with empty type list")
{
    GIVEN("any type and an empty type list")
    {
        THEN("count always returns 0")
        {
            REQUIRE(count<void>() == 0U);
            REQUIRE(count<int>() == 0U);
            REQUIRE(count<std::string>() == 0U);
            REQUIRE(count<struct X>() == 0U);
        }
    }
}

SCENARIO("count with strict matching strategy")
{
    GIVEN("a type, e.g. bool, and a list with other types")
    {
        THEN("'bool' is not found in {int, char, float, unsigned}")
        {
            REQUIRE(count<matching::strict, bool, int, char, float, unsigned>() == 0U);
        }
    }

    GIVEN("a type, e.g. int, and a list with several 'variations' of it: const, volatile, references")
    {
        THEN("'int' is found once in {int, int const, int volatile, int &, int const &, int &&}")
        {
            REQUIRE(count<matching::strict, int, int, int const, int volatile, int &, int const &, int &&>() == 1U);
        }

        THEN("'int' is found once in {int const, int, int volatile, int &, int const &, int &&}")
        {
            REQUIRE(count<matching::strict, int, int const, int, int volatile, int &, int const &, int &&>() == 1U);
        }

        THEN("'int' is found once in {int const, int volatile, int &, int const &, int &&, int}")
        {
            REQUIRE(count<matching::strict, int, int const, int volatile, int &, int const &, int &&, int>() == 1U);
        }
    }

    GIVEN("a pointer or C-style array, e.g. to/of int, and a list with pointers to int and C-style int arrays")
    {
        THEN("'int *' is found once in {int *, int const *, int *const, int const *const, int [], int const []}")
        {
            REQUIRE(count<matching::strict, int *, int *, int const *, int *const, int const *const, int [], int const []>() == 1U);
        }

        THEN("'int const *' is found once in {int *, int const *, int *const, int const *const, int [], int const []}")
        {
            REQUIRE(count<matching::strict, int const *, int *, int const *, int *const, int const *const, int [], int const []>() == 1U);
        }

        THEN("'int *const' is found once in {int *, int const *, int *const, int const *const, int [], int const []}")
        {
            REQUIRE(count<matching::strict, int *const, int *, int const *, int *const, int const *const, int [], int const []>() == 1U);
        }

        THEN("'int const *const' is found once in {int *, int const *, int *const, int const *const, int [], int const []}")
        {
            REQUIRE(count<matching::strict, int const *const, int *, int const *, int *const, int const *const, int [], int const []>() == 1U);
        }

        THEN("'int []' is found once in {int *, int const *, int *const, int const *const, int [], int const []}")
        {
            REQUIRE(count<matching::strict, int [], int *, int const *, int *const, int const *const, int [], int const []>() == 1U);
        }

        THEN("'int const []' is found once in {int *, int const *, int *const, int const *const, int [], int const []}")
        {
            REQUIRE(count<matching::strict, int const [], int *, int const *, int *const, int const *const, int [], int const []>() == 1U);
        }
    }

    GIVEN("a type, e.g. float, and a list with several types, including at least two floats")
    {
        THEN("'float' is found twice in {float, float}")
        {
            REQUIRE(count<matching::strict, float, float, float>() == 2U);
        }

        THEN("'float' is found twice in {float, int, float}")
        {
            REQUIRE(count<matching::strict, float, float, int, float>() == 2U);
        }

        THEN("'float' is found twice in {int, float, float}")
        {
            REQUIRE(count<matching::strict, float, int, float, float>() == 2U);
        }

        THEN("'float' is found twice in {int, float, int, float}")
        {
            REQUIRE(count<matching::strict, float, int, float, int, float>() == 2U);
        }

        THEN("'float' is found three times in {int, float, int, float, int, float, int}")
        {
            REQUIRE(count<matching::strict, float, int, float, int, float, int, float, int>() == 3U);
        }
    }
}

SCENARIO("count with relaxed matching strategy")
{
    GIVEN("a type, e.g. bool, and a list with other types")
    {
        THEN("'bool' is not found in {int, char, float, unsigned}")
        {
            REQUIRE(count<bool, int, char, float, unsigned>() == 0U);
        }
    }

    GIVEN("a type, e.g. int, and a list with several 'variations' of it: const, volatile, references")
    {
        THEN("'int' is found 6 times in {int, int const, int volatile, int &, int const &, int &&}")
        {
            REQUIRE(count<int, int, int const, int volatile, int &, int const &, int &&>() == 6U);
        }
    }

    GIVEN("a pointer or C-style array, e.g. to/of int, and a list with pointers to int and C-style int arrays")
    {
        THEN("'int *' is found three times in {int *, int *, int *const, int []}")
        {
            REQUIRE(count<int *, int *, int *const, int []>() == 3U);
        }

        THEN("'int *' is not found in {int const *, int const *const, int const []}")
        {
            REQUIRE(count<int *, int const *, int const *const, int const []>() == 0U);
        }

        THEN("'int const *' is found three times in {int const *, int const *const, int const []}")
        {
            REQUIRE(count<int const *, int const *, int const *const, int const []>() == 3U);
        }

        THEN("'int const *' is not found in {int *, int *const, int []}")
        {
            REQUIRE(count<int const *, int *, int *const, int []>() == 0U);
        }

        THEN("'int const *const' is found three times in {int const *, int const *const, int const []}")
        {
            REQUIRE(count<int const *const, int const *, int const *const, int const []>() == 3U);
        }

        THEN("'int const *const' is not found in {int *, int *const, int []}")
        {
            REQUIRE(count<int const *const, int *, int *const, int []>() == 0U);
        }

        THEN("'int []' is found three times in {int *, int *, int *const, int []}")
        {
            REQUIRE(count<int [], int *, int *const, int []>() == 3U);
        }

        THEN("'int []' is not found three times in {int *, int *, int *const, int []}")
        {
            REQUIRE(count<int [], int const *, int const *const, int const []>() == 0U);
        }

        THEN("'int const []' is found three times in {int const *, int const *const, int const []}")
        {
            REQUIRE(count<int const [], int const *, int const *const, int const []>() == 3U);
        }

        THEN("'int const []' is not found in {int *, int *const, int []}")
        {
            REQUIRE(count<int const [], int *, int *const, int []>() == 0U);
        }
    }
}
