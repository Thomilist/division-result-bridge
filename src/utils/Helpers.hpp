#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <string>
#include <vector>

#include <QString>
#include <QStringBuilder>

#include "ForwardDeclarations.hpp"

#include "../Division.hpp"

#include "../ResultSource.hpp"
#include "../Visibility.hpp"

#include "../../build/Secrets.hpp"

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
            static const QString gitHubPagesUrl();
            static const QString gitHubPagesDocsUrl();

            // MeOS
            static const QString meosName();
            static const QString meosUrl();
            static const QString meosDownloadUrl();
            static const QString meosDocUrl();
            static const QString meosInfoServerDocUrl();
            static const QString defaultMeosInfoServerAddress();

            // Divisionsmatchberegning
            static const QString diviNameShort();
            static const QString diviNameLong();
            static const QString diviExeName();
            static const QString diviDownloadUrl();
            static const QString diviGitHubRepoUrl();

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

            // Enums
            static const QString visibility(Visibility a_visibility);
            static Visibility visibility(const QString& a_visibility);
            static const QString resultSource(ResultSource a_result_source);
            static ResultSource resultSource(const QString& a_result_source);

            // Password
            static const QString passwordRegex();
            static const QString passwordDisclaimer();

            // Vertical padding
            static int verticalPadding();

            // Loggables
            static const QString loggable(const QString& a_loggable);
            static const QString loggableMain();
            static const QString loggableConfigValidator();
            static const QString loggableCoordinator();
            static const QString loggableVersionNotifier();
            static const QString loggableDivisionInterface();
            static const QString loggableMeosInterface();
            static const QString loggableWebserverInterface();
            static const QString loggableCompetitionCreationWizard();

            // Loggers
            static const QString logger(const QString& a_logger);
            static const QString loggerFile();
            static const QString loggerMain();
            static const QString loggerCompetitionCreationWizard();
    };
}

#endif // __HELPERS_H__