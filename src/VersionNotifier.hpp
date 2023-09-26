#ifndef __VERSIONNOTIFIER_H__
#define __VERSIONNOTIFIER_H__

#include <QObject>

#include "ForwardDeclarations.hpp"

#include "Helpers.hpp"
#include "Loggable.hpp"
#include "Logger.hpp"
#include "Version.hpp"

#include "MessageType.hpp"
#include "UpdateStatus.hpp"

namespace divi
{
    class VersionNotifier : public Loggable
    {
        public:
            VersionNotifier(
                Logger* a_log,
                Version* a_version,
                QObject* a_parent = nullptr);
            ~VersionNotifier();
        
        private:
            void notifyIfNewUpdate();

            Version* version;
    };
}

#endif // __VERSIONNOTIFIER_H__