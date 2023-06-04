#include <catch2/catch_test_macros.hpp>

#include <catch2/matchers/catch_matchers_floating_point.hpp>
using namespace Catch::Matchers;

#include <typelists.hxx>
using namespace pi::tl;

#include <toolbox.hxx>

namespace
{
    template <size_t I, typename ...TypeList>
    [[nodiscard]] decltype(auto) test_get(TypeList &&...arguments)
    {
        return get<I>(std::forward<TypeList>(arguments)...);
    }

    template <typename ...TypeList>
    [[nodiscard]] decltype(auto) test_get(size_t const index, TypeList &&...arguments)
    {
        return get<TypeList...>(index, std::forward<TypeList>(arguments)...);
    }

    template <matching Strategy, typename Default, typename ...TypeList>
    [[nodiscard]] auto test_get_or_initialize(Default default_value, TypeList &&...arguments)
    {
        if constexpr (Strategy == pi::tl::matching::strict)
            return get_or_initialize<Strategy, Default, TypeList...>(default_value, std::forward<TypeList>(arguments)...);
        else
            return get_or_initialize<Default, TypeList...>(default_value, std::forward<TypeList>(arguments)...);
    }
}

SCENARIO("get (index known at compile time)") // NOLINT(misc-use-anonymous-namespace)
{
    GIVEN("a type list with N arguments, N >= 1")
    {
        THEN("get<0> returns the first argument")
        {
            REQUIRE(test_get<0>(1, 2, 3, 4) == 1);
            REQUIRE(test_get<0>(true, 2.1, 3.1, '4') == true); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        }

        THEN("get<N-1> returns the last argument")
        {
            REQUIRE(test_get<0>(1) == 1);
            REQUIRE(test_get<1>(true, '4') == '4');
            REQUIRE(test_get<4>(10, 20, 30, 40, 50) == 50);
        }
    }
}

SCENARIO("get (index known at run time)") // NOLINT(misc-use-anonymous-namespace)
{
    GIVEN("a type list with N arguments, N >= 1 2")
    {
        THEN("get(M, ...), M >= N throws a out_of_range exception: index out of range")
        {
            REQUIRE_THROWS(test_get<size_t>(1ULL, 1ULL));
            REQUIRE_THROWS(test_get(2ULL, 1ULL, 2ULL));
            REQUIRE_THROWS(test_get<int>(1ULL, 1));
            REQUIRE_THROWS(test_get(2ULL, 1));
            REQUIRE_THROWS(test_get(3ULL, 1));
        }

        THEN("get(M, ...), M >= N does not throw exceptions")
        {
            REQUIRE_NOTHROW(test_get(0ULL, 1ULL));
            REQUIRE_NOTHROW(test_get(1ULL, 1ULL, 2ULL));
        }

        THEN("get(M, ...), M >= N returns the expected argument")
        {
            REQUIRE(test_get(0ULL, 1) == 1);
            REQUIRE(test_get(0ULL, true, '4') == true);
            REQUIRE(test_get(1ULL, true, '4') == '4');
            REQUIRE(test_get(4ULL, 10, 20, 30, 40, 50) == 50);
            REQUIRE(test_get(1ULL, 10, '2', 30, 40.0, 50) == '2');
            REQUIRE_THAT(test_get(3ULL, 10, '2', 30, 40.0, 50), WithinAbs(40.0, epsilon<double>));
        }
    }
}

SCENARIO("get_or_initialize with strict matching strategy") // NOLINT(misc-use-anonymous-namespace)
{
    GIVEN("a default value and a list of arguments")
    {
        THEN("returns the default value if there is no argument of the exact same type")
        {
            REQUIRE(test_get_or_initialize<matching::strict>(false, 1) == false);
            REQUIRE(test_get_or_initialize<matching::strict, int>({}, 1.0, true, '1', "1") == 0);
            auto i1{ 1 };
            REQUIRE(test_get_or_initialize<matching::strict>(zero<int>, i1) == 0);
            using namespace std::string_literals;
            auto s{ "string"s };
            REQUIRE(test_get_or_initialize<matching::strict>(""s, s) == ""s);
        }

        THEN("returns the first argument of the exact same type, not the default")
        {
            auto const i1 = 1;
            REQUIRE(test_get_or_initialize<matching::strict>(1, i1, 3, 4) == 3);
            REQUIRE_THAT(test_get_or_initialize<matching::strict>(0.0, 0, 0.5f, 1.0), WithinAbs(1.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            using namespace std::string_literals;
            REQUIRE(test_get_or_initialize<matching::strict>(""s, "string"s) == "string"s);
        }
    }
}

SCENARIO("get_or_initialize with relaxed matching strategy") // NOLINT(misc-use-anonymous-namespace)
{
    GIVEN("a default value and a list of arguments")
    {
        THEN("returns the default value if there is no argument of the same type")
        {
            REQUIRE_THAT(test_get_or_initialize<matching::relaxed>(zero<double>, 1, 2.0f), WithinAbs(0.0, epsilon<double>)); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
            REQUIRE(test_get_or_initialize<matching::relaxed>(0, 'c') == 0);
        }

        THEN("returns the first argument of the same type, not the default")
        {
            REQUIRE(test_get_or_initialize<matching::relaxed>(0, one<int>) == 1);
            auto i1{ 1 };
            REQUIRE(test_get_or_initialize<matching::relaxed>(0, i1) == one<int>);
            using namespace std::string_literals;
            auto s{ "string"s };
            REQUIRE(test_get_or_initialize<matching::relaxed>(""s, s) == "string"s);
        }
    }
}
