#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <string>
#include <vector>

#include <QString>
#include <QStringBuilder>

#include "ForwardDeclarations.hpp"

#include "Division.hpp"

#include "Visibility.hpp"

#include "../build/Secrets.hpp"

namespace divi
{
    class Helpers final
    {
        public:
            Helpers() = delete;

            // Project
            static const QString projectName();
            static const QString prettyProjectName();
            static const QString projectVersion();

            // Author
            static const QString authorName();
            static const QString authorUsername();
            static const QString authorEmail();
            static const QString authorClub();
            static const QString authorClubDomain();
        
            // Date and time formats
            static const QString dateFormat();
            static const QString timeFormat();
            static const QString dateTimeFormat();

            // GitHub
            static const QString gitHubUsername();
            static const QString gitHubUserUrl();
            static const QString gitHubRepoName();
            static const QString gitHubRepoUrl();
            static const QString gitHubWikiUrl();
            static const QString gitHubReleaseUrl();
            static const QString gitHubReleaseApiUrl();
            static const QString gitHubIssuesUrl();
            static const QString gitHubLicenseUrl();

            // MeOS
            static const QString meosUrl();
            static const QString meosDownloadUrl();
            static const QString meosDocUrl();
            static const QString meosInfoServerDocUrl();
            static const QString defaultMeosInfoServerAddress();

            // Divisionsmatchberegning
            static const QString divisionsmatchberegningExeName();
            static const QString divisionsmatchberegningDownloadUrl();
            static const QString divisionsmatchberegningGitHubRepoUrl();

            // Web server
            static const QString defaultWebServerAddress();
            static const QString addressEndingWithSlash(const QString& a_url);
            static const QString webserverPathPrefix();
            static const QString apiPingEndpoint();
            static const QString apiCreateEndpoint();
            static const QString apiUpdateMetaEndpoint();
            static const QString apiUpdateResultsEndpoint();
            static const QString apiDeleteResultsEndpoint();
            static const QString apiAnalyticsEndpoint(int a_competition_id);

            // HTTP
            static const QString userAgent();
            static const std::pair<std::string, std::string> userAgentHeaderField();
            static const std::pair<std::string, std::string> jsonContentHeaderField();
            static const std::pair<std::string, std::string> apiCompetitionIdHeaderField(int a_id);
            static const std::pair<std::string, std::string> apiPasswordHeaderField(const QString& a_password);
            static const std::pair<std::string, std::string> versionHeaderField();

            // Visibility enum
            static const QString visibility(Visibility a_visibility);

            // Password regex
            static const QString passwordRegex();

            // Password (in)security disclaimer
            static const QString passwordDisclaimer();

            // Vertical padding
            static int verticalPadding();
    };
}

#endif // __HELPERS_H__