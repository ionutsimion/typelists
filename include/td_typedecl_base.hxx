#ifndef PITYPELISTS_TD_TYPEDECL_BASE_HXX
#define PITYPELISTS_TD_TYPEDECL_BASE_HXX

namespace pi::td::internal
{
    template <typename Type>
    struct wrapper_for
    {
    private:
        [[maybe_unused]] Type data_;
    };

    template <typename Type>
    struct wrapper_for_fundamental
    {
        constexpr wrapper_for_fundamental() = default;

        template <std::convertible_to<Type> InitializerType>
        explicit constexpr wrapper_for_fundamental(InitializerType const value) noexcept
        : data_{ static_cast<Type>(value) }
        {
        }

        constexpr wrapper_for_fundamental(wrapper_for_fundamental &&) noexcept = default;
        constexpr wrapper_for_fundamental(wrapper_for_fundamental const &) noexcept = default;

        ~wrapper_for_fundamental() = default;

        constexpr wrapper_for_fundamental &operator =(wrapper_for_fundamental &&) noexcept = default;
        constexpr wrapper_for_fundamental &operator =(wrapper_for_fundamental const &) noexcept = default;

        template <std::convertible_to<Type> InitializerType>
        constexpr wrapper_for_fundamental &operator =(InitializerType &&value) noexcept
        {
            data_ = value;
            return *this;
        }

        template <std::convertible_to<Type> InitializerType>
        constexpr wrapper_for_fundamental &operator =(InitializerType const &value) noexcept
        {
            data_ = value;
            return *this;
        }

        constexpr operator Type() const noexcept // NOLINT(google-explicit-constructor)
        {
            return data_;
        }

    private:
        Type data_;
    };

    template <typename Type>
    using derived_from_or_wrapper_for = std::conditional_t<std::is_final_v<Type>, wrapper_for<Type>, Type>;

    template <typename Type>
    using typedecl_base = std::conditional_t<std::is_class_v<Type>, derived_from_or_wrapper_for<Type>, wrapper_for_fundamental<std::decay_t<Type>>>;
}

#endif //PITYPELISTS_TD_TYPEDECL_BASE_HXX
