#include "VersionNotifier.hpp"


namespace divi
{
    VersionNotifier::VersionNotifier(Version* a_version)
        : Loggable(Helpers::loggableVersionNotifier())
        , version(a_version)
    {
        attachLogging(Helpers::loggerFile());
        attachLogging(Helpers::loggerMain());
        
        notifyIfNewUpdate();
    }
    
    VersionNotifier::~VersionNotifier()
    { }
    
    void VersionNotifier::notifyIfNewUpdate()
    {
        if (!version->checkedRecently())
        {
            return;
        }

        if (version->isUpdateAvailable() != UpdateStatus::NewerAvailable)
        {
            return;
        }

        log(MessageType::Info, "Internal / Check Version", 0, "Update Available",
            QString()
            % "Version "
            % version->getUpstreamVersion()
            % " is available for "
            % "<a href=\""
            % Helpers::gitHubReleaseUrl()
            % "\">"
            % "download"
            % "</a>. "
            % "The current version is "
            % version->getCurrentVersion());
    }
}