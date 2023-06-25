#include <catch2/catch_test_macros.hpp>

#include <catch2/matchers/catch_matchers_floating_point.hpp>
using namespace Catch::Matchers;

#include <typelists.hxx>
using namespace pi::tl;

#include <toolbox.hxx>

using namespace std::string_literals;

namespace
{
    struct npc_t
    {
        std::string name;
        double x;
        double y;
        double z;
        int hp;
    };

    template <typename ...TypeList>
    auto validate_npc()
    {
        auto constexpr number_of_strings = count<std::string, TypeList...>();
        auto constexpr number_of_doubles = count<double, TypeList...>();
        auto constexpr number_of_ints = count<int, TypeList...>();
        auto constexpr number_of_arguments = sizeof...(TypeList);

        static_assert(number_of_strings + number_of_doubles + number_of_ints == number_of_arguments,
                      "Unexpected argument(s). Accepted arguments are (up to): 1·std::string (name), 3·doubles (x, y, z - position), 1·int (health points).");
        static_assert(number_of_strings <= 1ULL, "Too many std::string arguments. At most one is expected: the name of the NPC.");
        static_assert(number_of_doubles <= 3ULL, "Too many double arguments. At most three are expected: x, y and z (the position of the NPC, in this order).");
        static_assert(number_of_ints <= 1ULL, "Too many int arguments. At most one is expected: the health points of the NPC.");
    }

    template <typename ...TypeList>
    [[maybe_unused]] auto initialize1([[maybe_unused]] TypeList &&...arguments)
    {
        validate_npc<TypeList...>();

        npc_t npc{};
        npc.name = get_or_initialize("NPC 1"s, arguments...);
        npc.x = get_nth_or_initialize<1>(10.0, arguments...); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        npc.y = get_nth_or_initialize<2>(1.0, arguments...);
        npc.z = get_nth_or_initialize<3>(20.0, arguments...); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        npc.hp = get_or_initialize(100, arguments...); // NOLINT(cppcoreguidelines-avoid-magic-numbers)

        return npc;
    }

    template <typename ...TypeList>
    [[maybe_unused]] auto initialize2([[maybe_unused]] TypeList &&...arguments)
    {
        validate_npc<TypeList...>();

        npc_t npc{};
        npc.name = get_or_initialize("NPC 2"s, arguments...);
        npc.hp = get_or_initialize(200, arguments...); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        npc.x = get_nth_or_initialize<1>(-10.0, arguments...); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        npc.y = get_nth_or_initialize<2>(2.0, arguments...); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        npc.z = get_nth_or_initialize<3>(-20.0, arguments...); // NOLINT(cppcoreguidelines-avoid-magic-numbers)

        return npc;
    }
}

SCENARIO("sandbox (NPC)") // NOLINT(misc-use-anonymous-namespace)
{
    GIVEN("an instance of type NPC and an initialization function")
    {
        THEN("all data members are initialized with the implementer's defaults if no arguments are provided")
        {
            auto const npc1 = initialize1();
            REQUIRE(npc1.name == "NPC 1"s);
            REQUIRE_THAT(npc1.x, WithinAbs(10.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc1.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc1.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc1.hp == 100);

            auto const npc2 = initialize2();
            REQUIRE(npc2.name == "NPC 2"s);
            REQUIRE_THAT(npc2.x, WithinAbs(-10.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc2.y, WithinAbs(2.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc2.z, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc2.hp == 200);
        }

        THEN("if only one string argument is provided, only the name of the NPC will be different than the implementer's default")
        {
            auto const npc1 = initialize1("Batman"s);
            REQUIRE(npc1.name == "Batman"s);
            REQUIRE_THAT(npc1.x, WithinAbs(10.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc1.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc1.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc1.hp == 100);

            auto const npc2 = initialize2("Superman"s);
            REQUIRE(npc2.name == "Superman"s);
            REQUIRE_THAT(npc2.x, WithinAbs(-10.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc2.y, WithinAbs(2.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc2.z, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc2.hp == 200);
        }

        THEN("if only one int argument is provided, only the HP of the NPC will be different than the implementer's default")
        {
            auto const npc1 = initialize1(400);
            REQUIRE(npc1.name == "NPC 1"s);
            REQUIRE_THAT(npc1.x, WithinAbs(10.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc1.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc1.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc1.hp == 400);

            auto const npc2 = initialize2(1'000'000);
            REQUIRE(npc2.name == "NPC 2"s);
            REQUIRE_THAT(npc2.x, WithinAbs(-10.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc2.y, WithinAbs(2.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc2.z, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc2.hp == 1'000'000);
        }

        THEN("if only one double argument is provided, only the x position component of the NPC will be different than the implementer's default")
        {
            auto const npc1 = initialize1(100.0);
            REQUIRE(npc1.name == "NPC 1"s);
            REQUIRE_THAT(npc1.x, WithinAbs(100.0, epsilon<double>));
            REQUIRE_THAT(npc1.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc1.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc1.hp == 100);

            auto const npc2 = initialize2(-100.0);
            REQUIRE(npc2.name == "NPC 2"s);
            REQUIRE_THAT(npc2.x, WithinAbs(-100.0, epsilon<double>));
            REQUIRE_THAT(npc2.y, WithinAbs(2.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc2.z, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc2.hp == 200);
        }

        THEN("if only two double argument are provided, only the x and y position components of the NPC will be different than the implementer's default")
        {
            auto const npc1 = initialize1(100.0, 1.5);
            REQUIRE(npc1.name == "NPC 1"s);
            REQUIRE_THAT(npc1.x, WithinAbs(100.0, epsilon<double>));
            REQUIRE_THAT(npc1.y, WithinAbs(1.5, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc1.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc1.hp == 100);

            auto const npc2 = initialize2(-100.0, 100.0);
            REQUIRE(npc2.name == "NPC 2"s);
            REQUIRE_THAT(npc2.x, WithinAbs(-100.0, epsilon<double>));
            REQUIRE_THAT(npc2.y, WithinAbs(100.0, epsilon<double>));
            REQUIRE_THAT(npc2.z, WithinAbs(-20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc2.hp == 200);
        }

        THEN("if only three double argument are provided, only the position of the NPC will be different than the implementer's default")
        {
            auto const npc1 = initialize1(100.0, 1.5, 0.1);
            REQUIRE(npc1.name == "NPC 1"s);
            REQUIRE_THAT(npc1.x, WithinAbs(100.0, epsilon<double>));
            REQUIRE_THAT(npc1.y, WithinAbs(1.5, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc1.z, WithinAbs(0.1, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc1.hp == 100);

            auto const npc2 = initialize2(-100.0, 100.0, -0.1);
            REQUIRE(npc2.name == "NPC 2"s);
            REQUIRE_THAT(npc2.x, WithinAbs(-100.0, epsilon<double>));
            REQUIRE_THAT(npc2.y, WithinAbs(100.0, epsilon<double>));
            REQUIRE_THAT(npc2.z, WithinAbs(-0.1, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc2.hp == 200);
        }

        THEN("if an std::string, an int and one double are given, in whichever order, the name, HP and x coordinate will take their values")
        {
            auto const npc1 = initialize1("Batman"s, 400, 1'000.0);
            REQUIRE(npc1.name == "Batman"s);
            REQUIRE_THAT(npc1.x, WithinAbs(1'000.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc1.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc1.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc1.hp == 400);

            auto const npc2 = initialize1("Superman"s, 2'000.0, 1'000'000);
            REQUIRE(npc2.name == "Superman"s);
            REQUIRE_THAT(npc2.x, WithinAbs(2'000.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc2.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc2.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc2.hp == 1'000'000);

            auto const npc3 = initialize1(10'000, "Wolverine"s, 3'000.0);
            REQUIRE(npc3.name == "Wolverine"s);
            REQUIRE_THAT(npc3.x, WithinAbs(3'000.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc3.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc3.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc3.hp == 10'000);

            auto const npc4 = initialize1(4'000.0, "Iron Man"s, 1'000);
            REQUIRE(npc4.name == "Iron Man"s);
            REQUIRE_THAT(npc4.x, WithinAbs(4'000.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc4.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc4.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc4.hp == 1'000);

            auto const npc5 = initialize1(300'000, 5'000.0, "Alien"s);
            REQUIRE(npc5.name == "Alien"s);
            REQUIRE_THAT(npc5.x, WithinAbs(5'000.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc5.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc5.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc5.hp == 300'000);

            auto const npc6 = initialize1(6'000.0, 120, "Ripley"s);
            REQUIRE(npc6.name == "Ripley"s);
            REQUIRE_THAT(npc6.x, WithinAbs(6'000.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE_THAT(npc6.y, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc6.z, WithinAbs(20.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(npc6.hp == 120);
        }

        THEN("if all the parameters are provided, regardless of their order, all attributes are set with the values of the arguments (in order)")
        {
            auto const npc = initialize1(1.0, 10'000, 0.0, "Wolverine"s, -1.0);
            REQUIRE(npc.name == "Wolverine"s);
            REQUIRE_THAT(npc.x, WithinAbs(1.0, epsilon<double>));
            REQUIRE_THAT(npc.y, WithinAbs(0.0, epsilon<double>));
            REQUIRE_THAT(npc.z, WithinAbs(-1.0, epsilon<double>));
            REQUIRE(npc.hp == 10'000);
        }
    }
}
