#include <catch2/catch_test_macros.hpp>

#include <typelists.hxx>
using namespace pi::tl;

namespace
{
    template <typename SearchedType, matching strategy, typename ...TypeList>
    decltype(auto) test_get_argument_of_type([[maybe_unused]] TypeList &&...arguments)
    {
        return get<SearchedType, strategy>(std::forward<TypeList>(arguments)...);
    }
}

SCENARIO("get with strict matching strategy")
{
    GIVEN("a type list with at least one type and")
    {
        THEN("get<SearchedType> returns the first left or right reference to SearchedType argument")
        {
            using namespace std::string_literals;

            auto const an_int{ 1 };
            auto another_int{ 2 };
            auto another_int_for_reference{ 3 };
            auto const &a_const_reference_to_int{ another_int_for_reference };
            auto a_std_string{ "a std::string"s };

            REQUIRE(test_get_argument_of_type<int, matching::strict>(4, a_const_reference_to_int, another_int, a_std_string) == 4);
            REQUIRE(test_get_argument_of_type<int const &, matching::strict>(an_int, a_const_reference_to_int, another_int, a_std_string) == an_int);
            REQUIRE(test_get_argument_of_type<std::string, matching::strict>(an_int, a_const_reference_to_int, another_int, "a std::string"s) == a_std_string);
        }
    }
}
