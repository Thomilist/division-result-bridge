#ifndef __BASICCONCEPTS_H__
#define __BASICCONCEPTS_H__

#include <concepts>

#include "ForwardDeclarations.hpp"

namespace divi
{
    template<typename T, typename ... U>
    concept IsAnyOf = (std::same_as<T, U> || ...);
}

#endif // __BASICCONCEPTS_H__