#ifndef PITYPELISTS_TD_TYPEDECL_BASE_HXX
#define PITYPELISTS_TD_TYPEDECL_BASE_HXX

namespace pi::td::internal
{
    template <typename Type, typename Tag>
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

    template <typename Type, typename Tag>
    struct wrapper_for_fundamental
    {
        constexpr wrapper_for_fundamental() = default;
        constexpr wrapper_for_fundamental(wrapper_for_fundamental &&) = default;
        constexpr wrapper_for_fundamental(wrapper_for_fundamental const &) = default;

        explicit constexpr wrapper_for_fundamental(Type const value) noexcept
        : data_{ static_cast<Type>(value) }
        {
        }

        template <typename FromType, typename FromTag>
        wrapper_for_fundamental &operator =(wrapper_for_fundamental<FromType, FromTag> &&other) noexcept
        {
            static_assert(std::is_same_v<FromType, Type> && std::is_same_v<FromTag, Tag>, "You cannot implicitly convert between stron types.");

            data_ = std::forward<FromType>(other.data_);
            return *this;
        }

        template <typename FromType, typename FromTag>
        wrapper_for_fundamental &operator =(wrapper_for_fundamental<FromType, FromTag> const &other) noexcept
        {
            static_assert(std::is_same_v<FromType, Type> && std::is_same_v<FromTag, Tag>, "You cannot implicitly convert between stron types.");

            data_ = other.data_;
            return *this;
        }

        wrapper_for_fundamental &operator =(Type &&value) noexcept
        {
            data_ = std::forward<Type>(value);
            return *this;
        }

        wrapper_for_fundamental &operator =(Type const &value) noexcept
        {
            data_ = value;
            return *this;
        }

        ~wrapper_for_fundamental() = default;

        constexpr operator Type() const noexcept // NOLINT(google-explicit-constructor)
        {
            return data_;
        }

    private:
        Type data_;
    };

    template <typename Type, typename Tag>
    struct derived_from : public Type
    {
        using Type::Type;
        using Type::operator =;
    };

    template <typename Type, typename Tag>
    using derived_from_or_wrapper_for = std::conditional_t<std::is_final_v<Type>, wrapper_for_final<Type, Tag>, derived_from<Type, Tag>>;

    template <typename Type, typename Tag>
    using typedecl_base = std::conditional_t<std::is_class_v<Type>, derived_from_or_wrapper_for<Type, Tag>, wrapper_for_fundamental<Type, Tag>>;
}

#endif //PITYPELISTS_TD_TYPEDECL_BASE_HXX
