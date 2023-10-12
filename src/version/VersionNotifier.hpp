#ifndef __VERSIONNOTIFIER_H__
#define __VERSIONNOTIFIER_H__

#include "../utils/ForwardDeclarations.hpp"

#include "../utils/Helpers.hpp"
#include "../logging/Loggable.hpp"
#include "Version.hpp"

#include "../logging/MessageType.hpp"
#include "UpdateStatus.hpp"

namespace divi
{
    class VersionNotifier : public Loggable
    {
        public:
            VersionNotifier(Version* a_version);
            ~VersionNotifier();
        
        private:
            void notifyIfNewUpdate();

            Version* version;
    };
}

#endif // __VERSIONNOTIFIER_H__