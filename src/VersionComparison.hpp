#ifndef __VERSIONCOMPARISON_H__
#define __VERSIONCOMPARISON_H__

namespace divi
{
    enum class VersionComparison
    {
        NewerMajor,
        NewerMinor,
        NewerPatch,
        Equal,
        OlderPatch,
        OlderMinor,
        OlderMajor,
        Undefined
    };
}

#endif // __VERSIONCOMPARISON_H__