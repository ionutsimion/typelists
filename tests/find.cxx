#include <catch2/catch_test_macros.hpp>

#include <typelists.hxx>
using namespace pi::tl;

SCENARIO("find with strict matching strategy")
{
    GIVEN("a type, e.g. int, and a type list with the same type with or without modifiers")
    {
        THEN("'int' is found in {int} at index 0")
        {
            REQUIRE(find<matching::strict, int, int>() == 0);
        }

        THEN("'int' is not found in {int const}")
        {
            REQUIRE(find<matching::strict, int, int const>() == npos);
        }

        THEN("'int' is not found in {int volatile}")
        {
            REQUIRE(find<matching::strict, int, int volatile>() == npos);
        }
    }

    GIVEN("a type, e.g. int, and a type list with a reference to the same type")
    {
        THEN("'int' is not found in {int &}")
        {
            REQUIRE(find<matching::strict, int, int &>() == npos);
        }

        THEN("'int' is not found in {int const &}")
        {
            REQUIRE(find<matching::strict, int, int const &>() == npos);
        }

        THEN("'int' is not found in {int &&}")
        {
            REQUIRE(find<matching::strict, int, int &&>() == npos);
        }
    }

    GIVEN("a type, e.g. double const, and a type list with the same type with or without modifiers")
    {
        THEN("'double const' is not found in {double}")
        {
            REQUIRE(find<matching::strict, double const, double>() == npos);
        }

        THEN("'double const' is found in {double const} at index 0")
        {
            REQUIRE(find<matching::strict, double const, double const>() == 0);
        }

        THEN("'double const' is not found in {double volatile}")
        {
            REQUIRE(find<matching::strict, double const, double volatile>() == npos);
        }
    }

    GIVEN("a type, e.g. double const, and a type list with a reference to the same type")
    {
        THEN("'double const' is not found in {double &}")
        {
            REQUIRE(find<matching::strict, double const, double &>() == npos);
        }

        THEN("'double const' is not found in {double const &}")
        {
            REQUIRE(find<matching::strict, double const, double const &>() == npos);
        }

        THEN("'double const' is not found in {double &&}")
        {
            REQUIRE(find<matching::strict, double const, double &&>() == npos);
        }
    }

    GIVEN("a type, e.g. bool volatile, and a type list with the same type with or without modifiers")
    {
        THEN("'bool volatile' is not found in {bool}")
        {
            REQUIRE(find<matching::strict, bool volatile, bool>() == npos);
        }

        THEN("'bool volatile' is not found in {bool const}")
        {
            REQUIRE(find<matching::strict, bool volatile, bool const>() == npos);
        }

        THEN("'bool volatile' is found in {bool volatile} at index 0")
        {
            REQUIRE(find<matching::strict, bool volatile, bool volatile>() == 0);
        }
    }

    GIVEN("a type, e.g. bool volatile, and a type list with a reference to the same type")
    {
        THEN("'bool volatile' is not found in {bool &}")
        {
            REQUIRE(find<matching::strict, bool volatile, bool &>() == npos);
        }

        THEN("'bool volatile' is not found in {bool const &}")
        {
            REQUIRE(find<matching::strict, bool volatile, bool const &>() == npos);
        }

        THEN("'bool volatile' is not found in {bool &&}")
        {
            REQUIRE(find<matching::strict, bool volatile, bool &&>() == npos);
        }
    }

    GIVEN("a l-reference to a type, e.g. std::string, and a type list with the same type with or without modifiers")
    {
        THEN("'std::string &' is not found in {std::string}")
        {
            REQUIRE(find<matching::strict, std::string &, std::string>() == npos);
        }

        THEN("'std::string &' is not found in {std::string const}")
        {
            REQUIRE(find<matching::strict, std::string &, std::string const>() == npos);
        }

        THEN("'std::string &' is not found in {std::string volatile}")
        {
            REQUIRE(find<matching::strict, std::string &, std::string volatile>() == npos);
        }
    }

    GIVEN("a l-reference to a type, e.g. std::string &, and a type list with a reference to the same type")
    {
        THEN("'std::string &' is found in {std::string &} at index 0")
        {
            REQUIRE(find<matching::strict, std::string &, std::string &>() == 0);
        }

        THEN("'std::string const &' is not found in {std::string const &}")
        {
            REQUIRE(find<matching::strict, std::string &, std::string const &>() == npos);
        }

        THEN("'std::string const &' is not found in {std::string &&}")
        {
            REQUIRE(find<matching::strict, std::string &, std::string &&>() == npos);
        }
    }

    GIVEN("a l-reference to a constant type, eg. int const &, and a type list with the same type with or without modifiers")
    {
        THEN("'int const &' is not found in {int}")
        {
            REQUIRE(find<matching::strict, int const &, int>() == npos);
        }

        THEN("'int const &' is not found in {int const}")
        {
            REQUIRE(find<matching::strict, int const &, int const>() == npos);
        }

        THEN("'int const &' is not found in {int volatile}")
        {
            REQUIRE(find<matching::strict, int const &, int volatile>() == npos);
        }
    }

    GIVEN("a l-reference to a constant type, eg. int const &, and a type list with a reference to the same type")
    {
        THEN("'int const &' is not found in {int &}")
        {
            REQUIRE(find<matching::strict, int const &, int &>() == npos);
        }

        THEN("'int const &' is found in {int const &} at index 0")
        {
            REQUIRE(find<matching::strict, int const &, int const &>() == 0);
        }

        THEN("'int const &' is not found in {int &&}")
        {
            REQUIRE(find<matching::strict, int const &, int &&>() == npos);
        }
    }

    GIVEN("a r-reference to a type, eg. int &&, and a type list with the same type with or without modifiers")
    {
        THEN("'int &&' is not found in {int}")
        {
            REQUIRE(find<matching::strict, int &&, int>() == npos);
        }

        THEN("'int &&' is not found in {int const}")
        {
            REQUIRE(find<matching::strict, int &&, int const>() == npos);
        }

        THEN("'int &&' is not found in {int volatile}")
        {
            REQUIRE(find<matching::strict, int &&, int volatile>() == npos);
        }
    }

    GIVEN("a r-reference to a type, eg. int &&, and a type list with a reference to the same type")
    {
        THEN("'int &&' is not found in {int &}")
        {
            REQUIRE(find<matching::strict, int &&, int &>() == npos);
        }

        THEN("'int &&' is not found in {int const &&}")
        {
            REQUIRE(find<matching::strict, int &&, int const &>() == npos);
        }

        THEN("'int &&' is found in {int &&} at index 0")
        {
            REQUIRE(find<matching::strict, int &&, int &&>() == 0);
        }
    }

    GIVEN("a type, e.g. int, and a type list with at least one type, int being one of them")
    {
        THEN("'int' is found in {float, int} at index 1")
        {
            REQUIRE(find<matching::strict, int, float, int>() == 1);
        }

        THEN("'int' is found in {float, char, int} at index 2")
        {
            REQUIRE(find<matching::strict, int, float, char, int>() == 2);
        }

        THEN("'int' is found in {int const, int volatile, int &, int, int const &, int &&, int *} at index 3")
        {
            REQUIRE(find<matching::strict, int, int const, int volatile, int &, int, int const &, int &&, int *>() == 3);
        }

        THEN("'int' is found in {int const, int volatile, int &, int const &, int &&, int *, int} at index 6")
        {
            REQUIRE(find<matching::strict, int, int const, int volatile, int &, int const &, int &&, int *, int>() == 6);
        }
    }

    GIVEN("a type, e.g. int, and a type list without the same type in it")
    {
        THEN("'int' is not found in {unsigned}")
        {
            REQUIRE(find<matching::strict, int, unsigned>() == npos);
        }

        THEN("'int' is not found in {bool}")
        {
            REQUIRE(find<matching::strict, int, bool>() == npos);
        }

        THEN("'int' is not found in {unsigned char, double, float, std::string, void, std::nullptr_t}")
        {
            REQUIRE(find<matching::strict, int, unsigned char, double, float, std::string, void, std::nullptr_t>() == npos);
        }
    }
}

SCENARIO("find with strict relaxed strategy")
{
    GIVEN("a type, e.g. int, and a type list with the same type with or without modifiers")
    {
        THEN("'int' is found in {int} at index 0")
        {
            REQUIRE(find<int, int>() == 0);
        }

        THEN("'int' is found in {int const} at index 0")
        {
            REQUIRE(find<int, int const>() == 0);
        }

        THEN("'int' is not found in {int volatile} at index 0")
        {
            REQUIRE(find<int, int volatile>() == 0);
        }
    }

    GIVEN("a type, e.g. int, and a type list with a reference to the same type")
    {
        THEN("'int' is found in {int &} at index 0")
        {
            REQUIRE(find<int, int &>() == 0);
        }

        THEN("'int' is found in {int const &} at index 0")
        {
            REQUIRE(find<int, int const &>() == 0);
        }

        THEN("'int' is found in {int &&} at index 0")
        {
            REQUIRE(find<int, int &&>() == 0);
        }
    }
}

SCENARIO("find with nth appearance")
{
    GIVEN("a type, e.g. int, and a list of types, int appearing at least twice")
    {
        THEN("3rd 'int' is not found in {int, int}")
        {
            REQUIRE(find<int, 3, int, int>() == npos);
        }

        THEN("3rd 'int' is not found int {int, unsigned, int, bool}")
        {
            REQUIRE(find<int, 3, int, unsigned, int, bool>() == npos);
        }

        THEN("2nd 'int' is found in {int, int} at index 1")
        {
            REQUIRE(find<int, 2, int, int>() == 1);
        }

        THEN("2nd 'int' is found in {int, bool, unsigned, int} at index 3")
        {
            REQUIRE(find<int, 2, int, bool, unsigned, int>() == 3);
        }

        THEN("2nd 'int' is found in {int, const int, int &, int &&, int const &, int *, int} at index 6 with strict matching")
        {
            REQUIRE(find<matching::strict, int, 2, int, const int, int &, int &&, int const &, int *, int>() == 6);
        }
    }
}
