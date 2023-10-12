#ifndef __VERSIONCOMPARISON_H__
#define __VERSIONCOMPARISON_H__

namespace divi
{
    enum class VersionComparison
    {
        _Undefined,
        NewerMajor,
        NewerMinor,
        NewerPatch,
        Equal,
        OlderPatch,
        OlderMinor,
        OlderMajor
    };
}

#endif // __VERSIONCOMPARISON_H__