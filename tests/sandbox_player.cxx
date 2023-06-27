#include <catch2/catch_test_macros.hpp>

#include <catch2/matchers/catch_matchers_floating_point.hpp>
using namespace Catch::Matchers;

#include <typelists.hxx>
using namespace pi::tl;

#include <typedecl.hxx>
using namespace pi::td;

#include <toolbox.hxx>

using namespace std::string_literals;

namespace
{
    using name_t = typedecl<std::string, AUTO_TAG>;
    using x_t = typedecl<double, TAG(XAxis)>;
    using y_t = typedecl<double, TAG(YAxis)>;
    using z_t = typedecl<double, TAG(ZAxis)>;
    using health_t = typedecl<int, AUTO_TAG>;

    decltype(auto) constexpr operator ""_name(char const *string, unsigned long long)
    {
        return name_t{ string };
    }

    decltype(auto) constexpr operator ""_x(long double const value)
    {
        return x_t{ value };
    }

    decltype(auto) constexpr operator ""_x(unsigned long long const value)
    {
        return x_t{ value };
    }

    decltype(auto) constexpr operator ""_y(long double const value)
    {
        return y_t{ value };
    }

    decltype(auto) constexpr operator ""_y(unsigned long long const value)
    {
        return y_t{ value };
    }

    decltype(auto) constexpr operator ""_z(long double const value)
    {
        return z_t{ value };
    }

    decltype(auto) constexpr operator ""_z(unsigned long long const value)
    {
        return z_t{ value };
    }

    decltype(auto) constexpr operator ""_hp(unsigned long long const value)
    {
        return health_t{ value };
    }

    struct player_t
    {
        name_t name{};

        x_t x{};
        y_t y{};
        z_t z{};

        health_t hp{};
    };

    template <typename ...TypeList>
    auto validate_player()
    {
        auto constexpr number_of_names = count<name_t, TypeList...>();
        auto constexpr number_of_xs = count<x_t, TypeList...>();
        auto constexpr number_of_ys = count<y_t, TypeList...>();
        auto constexpr number_of_zs = count<z_t, TypeList...>();
        auto constexpr number_of_healths = count<health_t, TypeList...>();
        auto constexpr number_of_arguments = sizeof...(TypeList);

        static_assert(number_of_names + number_of_xs + number_of_ys + number_of_zs + number_of_healths == number_of_arguments,
                      "Unexpected argument type. Accepted argument types are: name_t, x_t, y_t, z_t and health_t.");
        static_assert(number_of_names <= 1ULL, "Too many name_t arguments. At most one is expected: the name of the Player.");
        static_assert(number_of_xs <= 1ULL, "Too many x_t arguments. At most one is expected: the x coordinate of the Player.");
        static_assert(number_of_ys <= 1ULL, "Too many y_t arguments. At most one is expected: the y coordinate of the Player.");
        static_assert(number_of_zs <= 1ULL, "Too many z_t arguments. At most one is expected: the z coordinate of the Player.");
        static_assert(number_of_healths <= 1ULL, "Too many health_t arguments. At most one is expected: the health points of the Player.");
    }

    template <typename ...TypeList>
    [[maybe_unused]] auto initialize1([[maybe_unused]] TypeList &&...arguments)
    {
        validate_player<TypeList...>();

        player_t player{};
        player.name = get_or_initialize("Player 1"_name, arguments...);
        player.x = get_or_initialize(100.0_x, arguments...);
        player.y = get_or_initialize(10.0_y, arguments...);
        player.z = get_or_initialize(200.0_z, arguments...);
        player.hp = get_or_initialize(100_hp, arguments...);

        return player;
    }

    template <typename ...TypeList>
    [[maybe_unused]] auto initialize2([[maybe_unused]] TypeList &&...arguments)
    {
        validate_player<TypeList...>();

        player_t player{};
        player.name = get_or_initialize("Player 2"_name, arguments...);
        player.hp = get_or_initialize(200_hp, arguments...);
        player.x = get_or_initialize(x_t{ -100.0 }, arguments...);
        player.y = get_or_initialize(y_t{ -20.0 }, arguments...);
        player.z = get_or_initialize(z_t{ -200.0 }, arguments...);

        return player;
    }
}

SCENARIO("sandbox (Player)") // NOLINT(misc-use-anonymous-namespace)
{
    GIVEN("an instance of type Player and an initialization function")
    {
        THEN("all data members are initialized with the implementer's defaults if no arguments are provided")
        {
            auto const player1 = initialize1();
            REQUIRE(player1.name == "Player 1"_name);
            REQUIRE_THAT(player1.x, WithinAbs(100.0_x, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.y, WithinAbs(10.0_y, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.z, WithinAbs(200.0_z, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player1.hp == 100_hp);

            auto const player2 = initialize2();
            REQUIRE(player2.name == "Player 2"s);
            REQUIRE_THAT(player2.x, WithinAbs(-100.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.y, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.z, WithinAbs(-200.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player2.hp == 200);
        }

        THEN("if only one name_t argument is provided, only the name of the Player will be different than the implementer's default")
        {
            auto const player1 = initialize1("Batman"_name);
            REQUIRE(player1.name == "Batman"_name);
            REQUIRE_THAT(player1.x, WithinAbs(100.0_x, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.y, WithinAbs(10.0_y, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.z, WithinAbs(200.0_z, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player1.hp == 100_hp);

            auto const player2 = initialize2("Superman"_name);
            REQUIRE(player2.name == "Superman");
            REQUIRE_THAT(player2.x, WithinAbs(-100.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.y, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.z, WithinAbs(-200.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player2.hp == 200);
        }

        THEN("if only one health_t argument is provided, only the HP of the Player will be different than the implementer's default")
        {
            auto const player1 = initialize1(400_hp);
            REQUIRE(player1.name == "Player 1"s);
            REQUIRE_THAT(player1.x, WithinAbs(100.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.y, WithinAbs(10.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.z, WithinAbs(200.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player1.hp == 400_hp);

            auto const player2 = initialize2(1'000'000_hp);
            REQUIRE(player2.name == "Player 2"s);
            REQUIRE_THAT(player2.x, WithinAbs(-100.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.y, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.z, WithinAbs(-200.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player2.hp == 1'000'000);
        }

        THEN("if only one x_t argument is provided, only the x position component of the Player will be different than the implementer's default")
        {
            auto const player1 = initialize1(1000.0_x);
            REQUIRE(player1.name == "Player 1"s);
            REQUIRE_THAT(player1.x, WithinAbs(1000.0_x, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.y, WithinAbs(10.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.z, WithinAbs(200.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player1.hp == 100);

            // I cannot use negatives with the user literal here, because it will be seen as a double inside the function.
            // This is due to automatic conversions, but, still, they do have their advantages
            auto const player2 = initialize2(x_t{ -1000.0 });
            REQUIRE(player2.name == "Player 2"s);
            REQUIRE_THAT(player2.x, WithinAbs(-1000.0_x, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.y, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.z, WithinAbs(-200.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player2.hp == 200);
        }

        THEN("if only one y_t argument is provided, only the y position component of the Player will be different than the implementer's default")
        {
            auto const player1 = initialize1(100.0_y);
            REQUIRE(player1.name == "Player 1"s);
            REQUIRE_THAT(player1.x, WithinAbs(100.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.y, WithinAbs(100.0_y, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.z, WithinAbs(200.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player1.hp == 100);

            // I cannot use negatives with the user literal here, because it will be seen as a double inside the function.
            // This is due to automatic conversions, but, still, they do have their advantages
            auto const player2 = initialize2(y_t{ -200.0 });
            REQUIRE(player2.name == "Player 2"s);
            REQUIRE_THAT(player2.x, WithinAbs(-100.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.y, WithinAbs(-200.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.z, WithinAbs(-200.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player2.hp == 200);
        }

        THEN("if only one z_t argument is provided, only the z position component of the Player will be different than the implementer's default")
        {
            auto const player1 = initialize1(2000.0_z);
            REQUIRE(player1.name == "Player 1"s);
            REQUIRE_THAT(player1.x, WithinAbs(100.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.y, WithinAbs(10.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.z, WithinAbs(2000.0_z, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player1.hp == 100);

            // I cannot use negatives with the user literal here, because it will be seen as a double inside the function.
            // This is due to automatic conversions, but, still, they do have their advantages
            auto const player2 = initialize2(z_t{ -2000.0 });
            REQUIRE(player2.name == "Player 2"s);
            REQUIRE_THAT(player2.x, WithinAbs(-100.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.y, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.z, WithinAbs(-2000.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player2.hp == 200);
        }

        THEN("if all expected arguments are given, but in random order, the correct values are assigned")
        {
            auto const player1 = initialize1(0_z, 0_x, 0_y, 1_hp, "P 1"_name);
            REQUIRE(player1.name == "P 1"_name);
            REQUIRE_THAT(player1.x, WithinAbs(0.0_x, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.y, WithinAbs(0.0_y, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player1.z, WithinAbs(0.0_z, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player1.hp == 1_hp);

            auto const player2 = initialize2(0_hp, 1_x, 1_y, 1_z, "Zombie"_name);
            REQUIRE(player2.name == "Zombie"s);
            REQUIRE_THAT(player2.x, WithinAbs(1.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.y, WithinAbs(1.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(player2.z, WithinAbs(1.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(player2.hp == 0);
        }
    }
}
