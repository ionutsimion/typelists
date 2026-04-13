#include <catch2/catch_test_macros.hpp>

#include <catch2/matchers/catch_matchers_floating_point.hpp>
using namespace Catch::Matchers;

#include <typelists/struct.hxx>
using namespace pi::tl;

#include <toolbox.hxx>

using x_t = pi::td::typedecl<double, AUTO_TAG>;
using y_t = pi::td::typedecl<double, AUTO_TAG>;
using z_t = pi::td::typedecl<double, AUTO_TAG>;
using pos3_t = pi::td::typedecl<struct_t<x_t, y_t, z_t>, AUTO_TAG>;
using pos2_t = pi::td::typedecl<struct_with_consts_t<x_t, y_t, z_t const>, AUTO_TAG>;

using red_t = pi::td::typedecl<double, TAG(ColorRed)>;
using green_t = pi::td::typedecl<double, TAG(ColorGreen)>;
using blue_t = pi::td::typedecl<double, TAG(ColorBlue)>;
using alpha_t = pi::td::typedecl<double, TAG(ColorAlpha)>;
using rgba_t = pi::td::typedecl<struct_t<red_t, green_t, blue_t, alpha_t>, TAG(ColorRGBA)>;
using rgb_t = pi::td::typedecl<struct_with_consts_t<red_t, green_t, blue_t, const alpha_t>, TAG(ColorRGBA)>;

x_t operator ""_x(long double x)
{
    return x_t{ static_cast<double>(x) };
}

x_t operator ""_x(unsigned long long x)
{
    return x_t{ static_cast<double>(x) };
}

y_t operator ""_y(long double x)
{
    return y_t{ static_cast<double>(x) };
}

y_t operator ""_y(unsigned long long x)
{
    return y_t{ static_cast<double>(x) };
}

z_t operator ""_z(long double x)
{
    return z_t{ static_cast<double>(x) };
}

z_t operator ""_z(unsigned long long x)
{
    return z_t{ static_cast<double>(x) };
}

SCENARIO("Struct")
{
    GIVEN("A 3D position")
    {
        pos3_t p{ 2.0_y, 1.0_x };

        THEN("Test 1")
        {
            REQUIRE_THAT(p.get<x_t>(), WithinAbs(1.0, pi::epsilon<double>));
            REQUIRE_THAT(p.get<y_t>(), WithinAbs(2.0, pi::epsilon<double>));
            REQUIRE_THAT(p.get<z_t>(), WithinAbs(0.0, pi::epsilon<double>));

            p.set(3_z);
            REQUIRE_THAT(p.get<z_t>(), WithinAbs(3.0, pi::epsilon<double>));
        }
    }

    GIVEN("Test 2")
    {
        rgba_t c{red_t{ 0.5 }, green_t{ 1.0 }, alpha_t{ 1.0 } };

        THEN("Let's see what happens")
        {
            REQUIRE_THAT(c.get<red_t>(), WithinAbs(0.5, pi::epsilon<double>));
            REQUIRE_THAT(c.get<green_t>(), WithinAbs(1.0, pi::epsilon<double>));
            REQUIRE_THAT(c.get<blue_t>(), WithinAbs(0.0, pi::epsilon<double>));
            REQUIRE_THAT(c.get<alpha_t>(), WithinAbs(1.0, pi::epsilon<double>));

            c.set(alpha_t{0.0});
            REQUIRE_THAT(c.get<alpha_t>(), WithinAbs(0.0, pi::epsilon<double>));
        }
    }

    GIVEN("A fixed integer 2D position")
    {
        using X = pi::td::typedecl<int, AUTO_TAG>;
        using Y = pi::td::typedecl<int, AUTO_TAG>;
        using Pos2D = struct_t<X, Y>;

        auto const x = X{ 1 };
        auto const y = Y{ 2 };
        auto const p = Pos2D{ x, y };

        THEN("Equality check passes against itself")
        {
            REQUIRE(p == p);
        }

        THEN("Equality check passes against another 2D position with the same coordinates")
        {
            REQUIRE(p == Pos2D{ x, Y{ 2 } });
            REQUIRE(Pos2D{ X{ 1 }, y } == p);
        }

        THEN("Equality check passes against a non-const position with the same coordinates")
        {
            auto q = Pos2D{ X{ 1 }, Y{ 2 } };
            REQUIRE(p == q);
            REQUIRE(q == p);
        }

        THEN("Equality check fails for two different positions")
        {
            REQUIRE(p != Pos2D{});
            REQUIRE(Pos2D{} != p);
        }
    }
}

SCENARIO("Struct with constants")
{
    GIVEN("A 2D position")
    {
        pos2_t p{ 1.0_x, 2.0_y, z_t{ 0.0 } };

        THEN("Test 1")
        {
            REQUIRE_THAT(p.get<x_t>(), WithinAbs(1.0, pi::epsilon<double>));
            REQUIRE_THAT(p.get<y_t>(), WithinAbs(2.0, pi::epsilon<double>));
            REQUIRE_THAT(p.get<z_t>(), WithinAbs(0.0, pi::epsilon<double>));

            //REQUIRE_THROWS(p.set(3_z));
            REQUIRE_THAT(p.get<z_t>(), WithinAbs(0.0, pi::epsilon<double>));
        }
    }

    GIVEN("Test 2")
    {
        rgb_t c{ red_t{ 0.5 }, green_t{ 1.0 }, blue_t{ 0.0 }, alpha_t{ 1.0 } };

        THEN("Let's see what happens")
        {
            REQUIRE_THAT(c.get<red_t>(), WithinAbs(0.5, pi::epsilon<double>));
            REQUIRE_THAT(c.get<green_t>(), WithinAbs(1.0, pi::epsilon<double>));
            REQUIRE_THAT(c.get<blue_t>(), WithinAbs(0.0, pi::epsilon<double>));
            REQUIRE_THAT(c.get<alpha_t>(), WithinAbs(1.0, pi::epsilon<double>));

            //REQUIRE_THROWS(c.set(alpha_t{ 0.0 }));
            REQUIRE_THAT(c.get<alpha_t>(), WithinAbs(1.0, pi::epsilon<double>));
        }
    }
}
