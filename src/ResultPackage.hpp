#ifndef __RESULTPACKAGE_H__
#define __RESULTPACKAGE_H__

#include <QByteArray>

#include "ForwardDeclarations.hpp"

namespace divi
{
    struct ResultPackage
    {
        int division_id;
        QByteArray result_file;
    };
}

#endif // __RESULTPACKAGE_H__