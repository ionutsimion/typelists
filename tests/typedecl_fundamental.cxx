#include <catch2/catch_test_macros.hpp>

#include <catch2/matchers/catch_matchers_floating_point.hpp>
using namespace Catch::Matchers;

#include <typedecl.hxx>
using namespace pi::td;

SCENARIO("given a strong type over a boolean")
{
    using boolean_t = typedecl<bool, TAG(Boolean)>;

    THEN("an instance can be default initialized and its value is false by default")
    {
        boolean_t constexpr b{};
        REQUIRE(b == false);
    }

    THEN("an instance can be initialized with a boolean value and can be compared to another instance or a bool")
    {
        boolean_t constexpr b1{ false };
        REQUIRE(b1 == false);
        boolean_t constexpr b2{ true };
        REQUIRE(b2 == true);
        REQUIRE(b1 != b2);
        REQUIRE(b1 == !b2);
    }

    THEN("an instance cannot be initialized with an instance of another strong type over boolean, without casting")
    {
        boolean_t b1{};
        typedecl<bool, AUTO_TAG> b2{ true };
        REQUIRE(b1 == false);
        REQUIRE(b1 != b2);
        b1 = static_cast<boolean_t>(b2);
        REQUIRE(b1 == b2);
    }

    THEN("an instance cannot be initialized with a boolean, without casting")
    {
        boolean_t b1{};
        REQUIRE(b1 == false);
        b1 = true;
        REQUIRE(b1 == true);
    }
}

SCENARIO("given a strong type over a char")
{
    using char_t = typedecl<char, TAG(Char)>;

    THEN("an instance can be default initialized and its value is 0 by default")
    {
        char_t constexpr c{};
        REQUIRE(c == 0);
        REQUIRE(c == '\0');
    }

    THEN("an instance can be default initialized with a char")
    {
        char_t constexpr c{ ' ' };
        REQUIRE(c == 32);
        REQUIRE(c == 0x20);
        REQUIRE(c == ' ');
        REQUIRE(c == " "[0]);
    }

    THEN("a value convertible to char can be assigned to an instance")
    {
        using namespace std::string_literals;

        char_t c{};
        REQUIRE(c == 0);
        c = char_t{ ' ' };
        REQUIRE(c == ' ');
        auto s = "a string"s;
        REQUIRE(c == s[1]);
        c = static_cast<char_t>(s[0]);
        REQUIRE(c == 'a');
        auto const *pc = "abc";
        REQUIRE(c == *pc);
        c = static_cast<char_t>(pc[2]);
        REQUIRE('c' == c);
    }
}
