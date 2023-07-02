#ifndef PITYPELISTS_TD_TYPEDECL_BASE_HXX
#define PITYPELISTS_TD_TYPEDECL_BASE_HXX

namespace pi::td::internal
{
    template <typename Type>
    struct wrapper_for_final
    {
        constexpr wrapper_for_final() noexcept = default;

        constexpr wrapper_for_final(wrapper_for_final &&)  noexcept = default;
        constexpr wrapper_for_final(wrapper_for_final const &) noexcept = default;

        constexpr explicit wrapper_for_final(Type &&data) noexcept
        : data_{ std::forward<Type>(data) }
        {
        }

        constexpr explicit wrapper_for_final(Type const &data) noexcept
                : data_{ data }
        {
        }

        wrapper_for_final &operator =(wrapper_for_final &&) noexcept = default;
        wrapper_for_final &operator =(wrapper_for_final const &) noexcept = default;

        template <std::convertible_to<Type> InitializerType>
        wrapper_for_final &operator =(InitializerType &&data) noexcept
        {
            data_ = std::forward<Type>(data);
            return *this;
        }

        template <std::convertible_to<Type> InitializerType>
        wrapper_for_final &operator =(InitializerType const &data) noexcept
        {
            data_ = static_cast<Type>(data);
            return *this;
        }

        std::add_lvalue_reference_t<std::add_const_t<Type>> operator *() const
        {
            return data_;
        }

        std::add_pointer_t<std::add_const_t<Type>> operator ->() const
        {
            return &data_;
        }

    private:
        Type data_;
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
    using derived_from_or_wrapper_for = std::conditional_t<std::is_final_v<Type>, wrapper_for_final<Type>, Type>;

    template <typename Type>
    using typedecl_base = std::conditional_t<std::is_class_v<Type>, derived_from_or_wrapper_for<Type>, wrapper_for_fundamental<Type>>;
}

#endif //PITYPELISTS_TD_TYPEDECL_BASE_HXX
