#include <catch2/catch_test_macros.hpp>

#include <typelists.hxx>
using namespace pi::tl;

namespace
{
    template <typename Type> auto constexpr zero = Type{};
    template <typename Type> auto constexpr one = Type{ 1 };

    template <std::floating_point Type>
    auto constexpr almost_equal(Type a, Type b)
    {
        return std::abs(std::abs(a) - std::abs(b)) <= std::numeric_limits<Type>::epsilon();
    }

    template <size_t I, typename ...TypeList>
    [[nodiscard]] decltype(auto) test_get(TypeList &&...arguments)
    {
        return get<I>(std::forward<TypeList>(arguments)...);
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

SCENARIO("get")
{
    GIVEN("a type list with N arguments, N >= 1")
    {
        THEN("get<0> returns the first argument")
        {
            REQUIRE(test_get<0>(1, 2, 3, 4) == 1);
            REQUIRE(test_get<0>(true, 2.1, 3.1, '4') == true);
        }

        THEN("get<N-1> returns the last argument")
        {
            REQUIRE(test_get<0>(1) == 1);
            REQUIRE(test_get<1>(true, '4') == '4');
            REQUIRE(test_get<4>(10, 20, 30, 40, 50) == 50);
        }
    }
}

SCENARIO("get_or_initialize with strict matching strategy")
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

        THEN("returns the first argument of the same type, not the default")
        {
            auto const i1 = 1;
            REQUIRE(test_get_or_initialize<matching::strict>(1, i1, 3, 4) == 3);
            REQUIRE(almost_equal(test_get_or_initialize<matching::strict>(0.0, 0, 0.5f, 1.0), 1.0));
            using namespace std::string_literals;
            REQUIRE(test_get_or_initialize<matching::strict>(""s, "string"s) == "string"s);
        }
    }
}

SCENARIO("get_or_initialize with relaxed matching strategy")
{
    GIVEN("a default value and a list of arguments")
    {
        THEN("returns the default value if there is no argument of the same type")
        {
            REQUIRE(almost_equal(test_get_or_initialize<matching::relaxed, double>(zero<int>, 1, 2.0f), 0.0));
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
