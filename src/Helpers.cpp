#include "Helpers.hpp"


namespace divi
{
    const QString Helpers::projectName()
    {
        return gitHubRepoName();
    }
    
    const QString Helpers::prettyProjectName()
    {
        return "Division Result Bridge";
    }
    
    const QString Helpers::projectVersion()
    {
        return "1.0.0";
    }
    
    const QString Helpers::authorName()
    {
        return "Thomas Emil Jensen";
    }
    
    const QString Helpers::authorUsername()
    {
        return gitHubUsername();
    }
    
    const QString Helpers::authorEmail()
    {
        return MY_EMAIL;
    }
    
    const QString Helpers::authorClub()
    {
        return "Horsens OK";
    }
    
    const QString Helpers::authorClubDomain()
    {
        return "https://horsensok.dk/";
    }

    const QString Helpers::dateFormat()
    {
        return "yyyy-MM-dd";
    }
    
    const QString Helpers::timeFormat()
    {
        return "hh:mm:ss";
    }
    
    const QString Helpers::dateTimeFormat()
    {
        return dateFormat() % " " % timeFormat();
    }
    
    const QString Helpers::gitHubUsername()
    {
        return "Thomilist";
    }
    
    const QString Helpers::gitHubUserUrl()
    {
        return "https://github.com/" % gitHubUsername() % "/";
    }
    
    const QString Helpers::gitHubRepoName()
    {
        return "division-result-bridge";
    }
    
    const QString Helpers::gitHubRepoUrl()
    {
        return gitHubUserUrl() % gitHubRepoName() % "/";
    }
    
    const QString Helpers::gitHubWikiUrl()
    {
        return gitHubRepoUrl() % "wiki/";
    }
    
    const QString Helpers::gitHubReleaseUrl()
    {
        return gitHubRepoUrl() % "releases/latest/";
    }
    
    const QString Helpers::gitHubReleaseApiUrl()
    {
        return "https://api.github.com/repos/" % gitHubUsername() % "/" % projectName() % "/releases";
    }
    
    const QString Helpers::gitHubIssuesUrl()
    {
        return gitHubRepoUrl() % "issues/";
    }
    
    const QString Helpers::gitHubLicenseUrl()
    {
        return gitHubRepoUrl() % "blob/main/LICENSE/";
    }
    
    const QString Helpers::meosUrl()
    {
        return "https://www.melin.nu/meos/en/";
    }
    
    const QString Helpers::meosDownloadUrl()
    {
        return meosUrl() % "download.php";
    }
    
    const QString Helpers::meosDocUrl()
    {
        return meosUrl() % "show.php";
    }
    
    const QString Helpers::meosInfoServerDocUrl()
    {
        return meosDocUrl() % "?base=4200&id=4242";
    }
    
    const QString Helpers::defaultMeosInfoServerAddress()
    {
        return "http://localhost:2009/meos";
    }
    
    const QString Helpers::divisionsmatchberegningExeName()
    {
        return "Divisionsmatch.exe";
    }
    
    const QString Helpers::divisionsmatchberegningDownloadUrl()
    {
        return "http://www.orientering.dk/divisionsmatch/";
    }
    
    const QString Helpers::divisionsmatchberegningGitHubRepoUrl()
    {
        return "https://github.com/AndersKlinting/divisionsmatchberegning";
    }
    
    const QString Helpers::defaultWebServerAddress()
    {
        return "http://152.70.60.26/";
    }
    
    const QString Helpers::addressEndingWithSlash(const QString& a_url)
    {
        if (a_url.isEmpty())
        {
            return "";
        }
        
        if (a_url.back() == '/')
        {
            return a_url;
        }
        
        return a_url % "/";
    }
    
    const QString Helpers::webserverPathPrefix()
    {
        return "";
    }
    
    const QString Helpers::apiPingEndpoint()
    {
        return webserverPathPrefix() % "api/ping";
    }
    
    const QString Helpers::apiCreateEndpoint()
    {
        return webserverPathPrefix() % "api/create";
    }
    
    const QString Helpers::apiUpdateMetaEndpoint()
    {
        return webserverPathPrefix() % "api/update/metadata";
    }
    
    const QString Helpers::apiUpdateResultsEndpoint()
    {
        return webserverPathPrefix() % "api/update/results";
    }
    
    const QString Helpers::apiDeleteResultsEndpoint()
    {
        return webserverPathPrefix() % "api/delete/results";
    }
    
    const QString Helpers::apiAnalyticsEndpoint(int a_competition_id)
    {
        return webserverPathPrefix() % "api/fetch/analytics/" % QString::number(a_competition_id);
    }
    
    const QString Helpers::userAgent()
    {
        return projectName() % "@" % authorUsername() % "/" % projectVersion();
    }
    
    const std::pair<std::string, std::string> Helpers::userAgentHeaderField()
    {
        return {"User-Agent", userAgent().toStdString()};
    }
    
    const std::pair<std::string, std::string> Helpers::jsonContentHeaderField()
    {
        return {"Content-Type", "application/json"};
    }
    
    const std::pair<std::string, std::string> Helpers::apiCompetitionIdHeaderField(int a_id)
    {
        return {"LDR-Competition-ID", std::to_string(a_id)};
    }
    
    const std::pair<std::string, std::string> Helpers::apiPasswordHeaderField(const QString& a_password)
    {
        return {"LDR-Password", a_password.toStdString()};
    }
    
    const std::pair<std::string, std::string> Helpers::versionHeaderField()
    {
        return {"LDR-Version", projectVersion().toStdString()};
    }
    
    const QString Helpers::visibility(Visibility a_visibility)
    {
        switch (a_visibility)
        {
            case Visibility::PUBLIC:
            {
                return "PUBLIC";
            }
            case Visibility::HIDDEN:
            {
                return "HIDDEN";
            }
            case Visibility::PRIVATE:
            {
                return "PRIVATE";
            }
        }

        return QString();
    }
    
    const QString Helpers::passwordRegex()
    {
        // Alphanumeric, no spaces
        return "^(\\w*)$";
    }
    
    const QString Helpers::passwordDisclaimer()
    {
        return QString()
            % "<i>"
            % "The password is stored in plain text and is therefore insecure. "
            % "Its only purpose is to prevent accidental access."
            % "</i>";
    }
    
    int Helpers::verticalPadding()
    {
        return 5;
    }
}