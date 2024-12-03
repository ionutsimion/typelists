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
        explicit struct_t(Arguments &&...args)
        {
            std::apply(  [this](decltype(args) ...args) { (set(std::forward<decltype(args)>(args)), ...); }
                       , std::make_tuple(args...));
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
}

#endif //PITYPELISTS_STRUCT_HXX
