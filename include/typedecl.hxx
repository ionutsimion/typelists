#ifndef PITYPELISTS_TYPEDECL_HXX
#define PITYPELISTS_TYPEDECL_HXX

#define AUTO_TAG TAG(__COUNTER__)
#define TAG(UniqueID) MAKE_TAG(UniqueID)
#define MAKE_TAG(ID) struct TAG_ ## ID

#include <td_typedecl_base.hxx>

namespace pi::td
{
    template<typename Type, typename Tag>
    struct typedecl : internal::typedecl_base<Type>
    {
        using internal::typedecl_base<Type>::typedecl_base;
        using internal::typedecl_base<Type>::operator =;
    };
}

#endif //PITYPELISTS_TYPEDECL_HXX
