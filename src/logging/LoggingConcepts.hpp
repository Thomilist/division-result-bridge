#ifndef __LOGGINGCONCEPTS_H__
#define __LOGGINGCONCEPTS_H__

#include <concepts>

#include "../utils/ForwardDeclarations.hpp"

#include "../utils/BasicConcepts.hpp"

namespace divi
{
    template<typename T>
    concept CanReferToLoggable = IsAnyOf<T, Loggable*, QString, QString&, const QString, const QString&>;

    template<typename T>
    concept CanReferToLogger = IsAnyOf<T, Logger*, QString, QString&, const QString, const QString&>;
}

#endif // __LOGGINGCONCEPTS_H__