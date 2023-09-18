#ifndef __UPDATESTATUS_H__
#define __UPDATESTATUS_H__

namespace divi
{
    enum class UpdateStatus
    {
        Unknown,
        NewerAvailable,
        UpToDate,
        Inaccessible
    };
}

#endif // __UPDATESTATUS_H__