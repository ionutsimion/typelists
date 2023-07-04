#include <catch2/catch_test_macros.hpp>

#include <catch2/matchers/catch_matchers_floating_point.hpp>
using namespace Catch::Matchers;

#include <typedecl.hxx>
using namespace pi::td;

#include <toolbox.hxx>

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

SCENARIO("given a strong type over an integer")
{
    using natural_t = typedecl<uint64_t, TAG(Natural)>;
    using integer_t = typedecl<int64_t, TAG(Integer)>;

    THEN("an instance can be default initialized and its value is 0 by default")
    {
        natural_t constexpr n{};
        integer_t constexpr i{};
        REQUIRE(n == 0U);
        REQUIRE(i == 0);
    }

    THEN("an instance can be default initialized with a convertible value")
    {
        natural_t constexpr n{ 1 };
        integer_t constexpr i{ -1 };
        REQUIRE(n == 1U);
        REQUIRE(i == -1);
    }

    THEN("a value convertible to natural/integer can be assigned to an instance")
    {
        natural_t n{};
        integer_t i{};

        n = natural_t{ 1U };
        i = integer_t{ -1 };
        REQUIRE(n == 1);
        REQUIRE(i == -1);

        n = static_cast<natural_t>(i);
        REQUIRE(n == static_cast<natural_t>(i));

        n = natural_t{ 2 };
        i = -static_cast<integer_t>(static_cast<integer_t::value_type>(n));
        REQUIRE(i == -2);

        natural_t m{ 3 };
        integer_t j{ 3 };
        std::swap(n, m);
        std::swap(i, j);
        REQUIRE(n == 3);
        REQUIRE(m == 2);
        REQUIRE(i == 3);
        REQUIRE(j == -2);
    }
}

SCENARIO("given a strong type over a floating point number")
{
    using single_precision_t = typedecl<float, TAG(Float)>;
    using double_precision_t = typedecl<double, TAG(Double)>;

    THEN("an instance can be default initialized and its value is 0 by default")
    {
        single_precision_t constexpr f{};
        double_precision_t constexpr r{};
        REQUIRE_THAT(f, WithinAbs(0.0f, pi::epsilon<float>));
        REQUIRE_THAT(r, WithinAbs(0.0, pi::epsilon<double>));
    }

    THEN("an instance can be default initialized with a convertible value")
    {
        single_precision_t constexpr f{ 3.1415926f };
        double_precision_t constexpr r{ 3.141592658979323846 };
        REQUIRE_THAT(f, WithinAbs(3.141593f, 1.E-6f));
        REQUIRE_THAT(f, !WithinAbs(3.141593f, 1.E-7f));
        REQUIRE_THAT(r, WithinAbs(3.141592658979324, 1.E-15));
        REQUIRE_THAT(r, !WithinAbs(3.141592658979324, 1.E-16));
    }

    THEN("a value convertible to natural/integer can be assigned to an instance")
    {
        single_precision_t f{};
        double_precision_t r{};

        f = single_precision_t{ pi::one<float> };
        r = double_precision_t{ pi::one<double> };
        REQUIRE_THAT(f, WithinAbs(1.0f, pi::epsilon<float>));
        REQUIRE_THAT(r, WithinAbs(1.0, pi::epsilon<double>));

        f = single_precision_t{ 2.0 };
        r = double_precision_t{ 2.0f };
        REQUIRE_THAT(f, WithinAbs(2.0f, pi::epsilon<float>));
        REQUIRE_THAT(r, WithinAbs(2.0, pi::epsilon<double>));

        f = single_precision_t{ 3 };
        r = double_precision_t{ 3 };
        REQUIRE_THAT(f, WithinAbs(3.0f, pi::epsilon<float>));
        REQUIRE_THAT(r, WithinAbs(3.0, pi::epsilon<double>));

        auto constexpr f2 = single_precision_t{ 4.0 };
        auto constexpr r2 = double_precision_t{ 4.0 };
        f = single_precision_t{ static_cast<single_precision_t::value_type>(r2) };
        r = double_precision_t{ f2 };
        REQUIRE_THAT(f, WithinAbs(4.0f, pi::epsilon<float>));
        REQUIRE_THAT(r, WithinAbs(4.0, pi::epsilon<double>));

        typedecl<float, AUTO_TAG> f3{};
        typedecl<double, AUTO_TAG> r3{};
        f = static_cast<single_precision_t>(f3);
        r = static_cast<double_precision_t>(r3);
        REQUIRE_THAT(f, WithinAbs(0.0f, pi::epsilon<float>));
        REQUIRE_THAT(r, WithinAbs(0.0, pi::epsilon<double>));
    }

    THEN("Math functions can be used with the strong type instances")
    {
        single_precision_t constexpr f{ 3.1415926f };
        double_precision_t constexpr r{ 3.141592658979323846 };
        REQUIRE_THAT(std::sin(f), WithinAbs(0.0f, 1.E-5));
        REQUIRE_THAT(std::cos(r), WithinAbs(-1.0, 1.E-10));
    }

    THEN("Instances of the same type can be added, multiplied etc.")
    {
        double_precision_t constexpr r{ 3.141592658979323846 };
        double_precision_t constexpr two{ 2.0 };

        REQUIRE_THAT(r + r, WithinAbs(r * two, pi::epsilon<double>));
        REQUIRE_THAT(r - r, WithinAbs(0.0, pi::epsilon<double>));
        REQUIRE_THAT(r / r, WithinAbs(1.0, pi::epsilon<double>));
    }
}
