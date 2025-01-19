#ifndef PITYPELISTS_STRUCT_HXX
#define PITYPELISTS_STRUCT_HXX

#include <typedecl.hxx>
#include <typelists.hxx>

namespace pi::tl
{
    template <typename ...TypeList>
    struct struct_t
    {
        template <typename ...Arguments>
        explicit struct_t(Arguments &&...arguments)
        {
            std::apply(  [this](decltype(arguments) ...args) { (set(std::forward<decltype(arguments)>(args)), ...); }
                       , std::make_tuple(arguments...));
        }

        template <typename Type>
        [[nodiscard]] decltype(auto) constexpr get()
        {
            return std::get<find<Type, TypeList...>()>(data_);
        }

        template <typename Type>
        auto set(Type &&value)
        {
            std::get<find<Type, TypeList...>()>(data_) = std::forward<Type>(value);
        }

    private:
        std::tuple<TypeList...> data_{};
    };

    template <typename ...TypeList>
    struct struct_with_consts_t
        : std::tuple<TypeList...>
    {
        template <typename ...Arguments>
        explicit struct_with_consts_t(Arguments &&...arguments)
            : std::tuple<TypeList...>(std::forward<Arguments>(arguments)...)
        {
        }

        template <typename Type>
        [[nodiscard]] decltype(auto) constexpr get()
        {
            return std::get<find<Type, TypeList...>()>(*this);
        }

        template <typename Type>
        auto set(Type &&value)
        {
            if constexpr (std::is_const_v<decltype(tl::get<tl::find<Type, TypeList...>()>(std::forward<TypeList>(TypeList{})...))>)
                throw std::invalid_argument("Trying to change the value of a constant.");
            else
                std::get<tl::find<Type, TypeList...>()>(*this) = std::forward<Type>(value);
        }
    };
}

#endif //PITYPELISTS_STRUCT_HXX
