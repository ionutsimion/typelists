#include <catch2/catch_test_macros.hpp>

#include <typelist.hxx>
using namespace pi::tl;

SCENARIO("index_of with strict matching strategy and a type list with one type")
{
    GIVEN("a type, e.g. int, it is found only when checked against int")
    {
        THEN("index_of<matching::strict, int, int>() returns 0")
        {
            REQUIRE(index_of<matching::strict, int, int>() == 0);
        }

        THEN("index_of<matching::strict, int, int const>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int, int const>() == npos);
        }

        THEN("index_of<matching::strict, int, int volatile>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int, int volatile>() == npos);
        }

        THEN("index_of<matching::strict, int, int &>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int, int &>() == npos);
        }

        THEN("index_of<matching::strict, int, int const &>() returns() npos")
        {
            REQUIRE(index_of<matching::strict, int, int const &>() == npos);
        }

        THEN("index_of<matching::strict, int, int &&>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int, int &&>() == npos);
        }
    }

    GIVEN("a type, e.g. double const, it is found only when checked against double const")
    {
        THEN("index_of<matching::strict, double const, double>() returns npos")
        {
            REQUIRE(index_of<matching::strict, double const, double>() == npos);
        }

        THEN("index_of<matching::strict, double const, double const>() returns 0")
        {
            REQUIRE(index_of<matching::strict, double const, double const>() == 0);
        }

        THEN("index_of<matching::strict, double const, double volatile>() returns npos")
        {
            REQUIRE(index_of<matching::strict, double const, double volatile>() == npos);
        }

        THEN("index_of<matching::strict, double const, double &>() returns npos")
        {
            REQUIRE(index_of<matching::strict, double const, double &>() == npos);
        }

        THEN("index_of<matching::strict, double const, double const &>() returns npos")
        {
            REQUIRE(index_of<matching::strict, double const, double const &>() == npos);
        }

        THEN("index_of<matching::strict, double const, double &&>() returns npos")
        {
            REQUIRE(index_of<matching::strict, double const, double &&>() == npos);
        }
    }

    GIVEN("a type, e.g. bool volatile, it is found only when checked against bool volatile")
    {
        THEN("index_of<matching::strict, bool volatile, bool>() returns npos")
        {
            REQUIRE(index_of<matching::strict, bool volatile, bool>() == npos);
        }

        THEN("index_of<matching::strict, bool volatile, bool const>() returns npos")
        {
            REQUIRE(index_of<matching::strict, bool volatile, bool const>() == npos);
        }

        THEN("index_of<matching::strict, bool volatile, bool volatile>() == 0")
        {
            REQUIRE(index_of<matching::strict, bool volatile, bool volatile>() == 0);
        }

        THEN("index_of<matching::strict, bool volatile, bool &>() returns npos")
        {
            REQUIRE(index_of<matching::strict, bool volatile, bool &>() == npos);
        }

        THEN("index_of<matching::strict, bool volatile, bool const &>() returns npos")
        {
            REQUIRE(index_of<matching::strict, bool volatile, bool const &>() == npos);
        }

        THEN("index_of<matching::strict, bool volatile, bool &&>() returns npos")
        {
            REQUIRE(index_of<matching::strict, bool volatile, bool &&>() == npos);
        }
    }

    GIVEN("a l-reference to a type, e.g. std::string, it is found only when checked against std::string &")
    {
        THEN("index_of<matching::strict, std::string &, std::string>() returns npos")
        {
            REQUIRE(index_of<matching::strict, std::string &, std::string>() == npos);
        }

        THEN("index_of<matching::strict, std::string &, std::string const>() returns npos")
        {
            REQUIRE(index_of<matching::strict, std::string &, std::string const>() == npos);
        }

        THEN("index_of<matching::strict, std::string &, std::string volatile>() returns npos")
        {
            REQUIRE(index_of<matching::strict, std::string &, std::string volatile>() == npos);
        }

        THEN("index_of<matching::strict, std::string &, std::string &>() == 0")
        {
            REQUIRE(index_of<matching::strict, std::string &, std::string &>() == 0);
        }

        THEN("index_of<matching::strict, std::string &, std::string const &>() returns npos")
        {
            REQUIRE(index_of<matching::strict, std::string &, std::string const &>() == npos);
        }

        THEN("index_of<matching::strict, std::string &, std::string &&>() returns npos")
        {
            REQUIRE(index_of<matching::strict, std::string &, std::string &&>() == npos);
        }
    }

    GIVEN("a l-reference to a constant type, eg. int const &, it is found only when checked against int const &")
    {
        THEN("index_of<matching::strict, int const &, int>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int const &, int>() == npos);
        }

        THEN("index_of<matching::strict, int const &, int const>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int const &, int const>() == npos);
        }

        THEN("index_of<matching::strict, int const &, int volatile>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int const &, int volatile>() == npos);
        }

        THEN("index_of<matching::strict, int const &, int &>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int const &, int &>() == npos);
        }

        THEN("index_of<matching::strict, int const &, int const &>() == 0")
        {
            REQUIRE(index_of<matching::strict, int const &, int const &>() == 0);
        }

        THEN("index_of<matching::strict, int const &, int &&>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int const &, int &&>() == npos);
        }
    }

    GIVEN("a r-reference to a type, eg. int &&, it is found only when checked against int &&")
    {
        THEN("index_of<matching::strict, int &&, int>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int &&, int>() == npos);
        }

        THEN("index_of<matching::strict, int &&, int const>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int &&, int const>() == npos);
        }

        THEN("index_of<matching::strict, int &&, int volatile>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int &&, int volatile>() == npos);
        }

        THEN("index_of<matching::strict, int &&, int &>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int &&, int &>() == npos);
        }

        THEN("index_of<matching::strict, int &&, int const &>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int &&, int const &>() == npos);
        }

        THEN("index_of<matching::strict, int &&, int &&>() == 0")
        {
            REQUIRE(index_of<matching::strict, int &&, int &&>() == 0);
        }
    }

    GIVEN("a type, e.g. int, it is not found when checked against other types")
    {
        THEN("index_of<matching::strict, int, unsigned>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int, unsigned>() == npos);
        }

        THEN("index_of<matching::strict, int, bool>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int, bool>() == npos);
        }
    }
}

SCENARIO("index_of with strict matching strategy and a type list with more than one type")
{
    GIVEN("a type, e.g. int, it is not found when it is not in the type list")
    {
        THEN("index_of<matching::strict, int, unsigned, flat, std::string>() returns npos")
        {
            REQUIRE(index_of<matching::strict, int, unsigned, float, std::string>() == npos);
        }
    }

    GIVEN("a type, e.g. int, it is found at the correct 0-based index in the type list")
    {
        THEN("index_of<matching::strict, int, float, int>() returns 1")
        {
            REQUIRE(index_of<matching::strict, int, float, int>() == 1);
        }

        THEN("index_of<matching::strict, int, float, char, int>() returns 2")
        {
            REQUIRE(index_of<matching::strict, int, float, char, int>() == 2);
        }

        THEN("index_of<matching::strict, int, int const, int volatile, int &, int, int const &, int &&, int *>() returns 3")
        {
            REQUIRE(index_of<matching::strict, int, int const, int volatile, int &, int, int const &, int &&, int *>() == 3);
        }

        THEN("index_of<matching::strict, int, int const, int volatile, int &, int const &, int &&, int *, int>() returns 6")
        {
            REQUIRE(index_of<matching::strict, int, int const, int volatile, int &, int const &, int &&, int *, int>() == 6);
        }
    }
}
