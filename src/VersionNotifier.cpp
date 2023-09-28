#include "VersionNotifier.hpp"


namespace divi
{
    VersionNotifier::VersionNotifier(
        Logger* a_log,
        Version* a_version,
        QObject* a_parent)
        : Loggable(a_log, a_parent)
        , version(a_version)
    {
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