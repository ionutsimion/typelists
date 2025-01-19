#include <catch2/catch_test_macros.hpp>

#include <catch2/matchers/catch_matchers_floating_point.hpp>
using namespace Catch::Matchers;

#include <typedecl.hxx>
using namespace pi::td;

namespace
{
    class user_defined_t
    {
    public:
        [[nodiscard]] inline auto get() const { return data_; }
        inline auto set(int const data) { data_ = data; };

        inline bool operator ==(user_defined_t const &other) const { return data_ == other.data_ && comment == other.comment; }

        std::string comment{};

    protected:
        int data_{};
    };

    class derived_user_defined_t
            : public user_defined_t
    {
    public:
        inline auto negate() { data_ = -data_; comment = std::string{ "negated" }; };
    };
}

SCENARIO("given a strong type over a user class")
{
    using safe_user_defined_t = typedecl<user_defined_t, AUTO_TAG>;
    using namespace std::string_literals;

    THEN("an instance can be default initialized and its value is a default initialized instance of the class")
    {
        safe_user_defined_t const c{};
        REQUIRE(c == user_defined_t{});
    }

    THEN("the member function and data can be directly accessed")
    {
        safe_user_defined_t c{};
        REQUIRE(c.get() == 0);
        REQUIRE(c.comment.empty());

        c.set(1);
        c.comment = "changed to 1"s;
        REQUIRE(c.get() == 1);
        REQUIRE(c.comment == "changed to 1"s);
    }

    THEN("the instance can take the values of instance convertible to it when = operator is used (with proper casting)")
    {
        safe_user_defined_t c1{};
        REQUIRE(c1.get() == 0);
        REQUIRE(c1.comment.empty());

        user_defined_t c2{};
        c2.set(2);
        c2.comment = "changed to 2"s;
        REQUIRE(c2.get() == 2);
        REQUIRE(c2.comment == "changed to 2"s);

        c1 = c2;
        REQUIRE(c1.get() == 2);
        REQUIRE(c1.comment == "changed to 2"s);

        user_defined_t c3{};
        c3.set(3);
        c3.comment = "changed to 3"s;
        REQUIRE(c3.get() == 3);
        REQUIRE(c3.comment == "changed to 3"s);

        c1 = c3;
        REQUIRE(c1.get() == 3);
        REQUIRE(c1.comment == "changed to 3"s);

        c1 = static_cast<user_defined_t>(typedecl<user_defined_t, AUTO_TAG>{});
        REQUIRE(c1.get() == 0);
        REQUIRE(c1.comment.empty());
    }
}

SCENARIO("given a strong type over a derived user class")
{
    using safe_derived_user_defined_t = typedecl<derived_user_defined_t, AUTO_TAG>;
    using namespace std::string_literals;

    THEN("an instance can be default initialized and its value is a default initialized instance of the class")
    {
        safe_derived_user_defined_t const d{};
        REQUIRE(d == derived_user_defined_t{});
    }

    THEN("the member function and data can be directly accessed")
    {
        safe_derived_user_defined_t d{};
        REQUIRE(d.get() == 0);
        REQUIRE(d.comment.empty());

        d.set(1);
        d.comment = "changed to 1"s;
        REQUIRE(d.get() == 1);
        REQUIRE(d.comment == "changed to 1"s);

        d.negate();
        REQUIRE(d.get() == -1);
        REQUIRE(d.comment == "negated"s);
    }

    THEN("the instance can take the values of instance convertible to it when = operator is used (with proper casting)")
    {
        safe_derived_user_defined_t d1{};
        REQUIRE(d1.get() == 0);
        REQUIRE(d1.comment.empty());

        derived_user_defined_t d2{};
        d2.set(2);
        d2.comment = "changed to 2"s;
        REQUIRE(d2.get() == 2);
        REQUIRE(d2.comment == "changed to 2"s);

        d1 = d2;
        REQUIRE(d1.get() == 2);
        REQUIRE(d1.comment == "changed to 2"s);

        derived_user_defined_t d3{};
        d3.set(3);
        d3.comment = "changed to 3"s;
        REQUIRE(d3.get() == 3);
        REQUIRE(d3.comment == "changed to 3"s);
        d3.negate();

        d1 = d3;
        REQUIRE(d1.get() == -3);
        REQUIRE(d1.comment == "negated"s);

        d1 = static_cast<derived_user_defined_t>(typedecl<derived_user_defined_t, AUTO_TAG>{});
        REQUIRE(d1.get() == 0);
        REQUIRE(d1.comment.empty());

        user_defined_t c{};
        c.set(4);
        c.comment = "changed to 4"s;

        d1 = static_cast<derived_user_defined_t>(c);
        REQUIRE(d1.get() == 4);
        REQUIRE(d1.comment == "changed to 4"s);
    }
}

SCENARIO("given a strong type over standard library string")
{
    using safe_string_t = typedecl<std::string, AUTO_TAG>;
    using namespace std::string_literals;
    using namespace std::string_view_literals;

    THEN("an instance can be default initialized and the underlying string is empty")
    {
        safe_string_t const s{};
        REQUIRE(s.empty());
    }

    THEN("an instance can be changed using = operator (with casting where necessary)")
    {
        safe_string_t s{};

        s = "char *";
        REQUIRE(s == "char *");

        s.clear();
        REQUIRE(s.empty());

        s = "string_view"sv;
        REQUIRE(s == "string_view"sv);

        s = "string"s;
        REQUIRE(s == "string"s);

        s = static_cast<safe_string_t>(typedecl<std::string, AUTO_TAG>{}.data());
        REQUIRE(s.empty());
    }

    THEN("algorithms and iterators can be used as with 'unsafe' string")
    {
        safe_string_t s{};

        s.resize(10);
        std::generate(s.begin(), s.end(), [i = 0]() mutable { return '0' + i++; });
        REQUIRE(s == "0123456789"s);

        std::reverse(s.begin(), s.end());
        REQUIRE(s == "9876543210"s);
    }
}
