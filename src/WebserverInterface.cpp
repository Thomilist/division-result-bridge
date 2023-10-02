#include "WebserverInterface.hpp"


namespace divi
{
    WebserverInterface::WebserverInterface(
        Logger* a_log,
        Settings* a_settings,
        QObject* a_parent)
        : Loggable(a_log, a_parent)
        , settings(a_settings)
    { }
    
    WebserverInterface::~WebserverInterface()
    { }
    
    const QString WebserverInterface::getMetadataAlias()
    {
        return "metadata";
    }
    
    const QString WebserverInterface::getResultsAlias()
    {
        return "results";
    }
    
    const QString WebserverInterface::getHtmlAlias()
    {
        return "html";
    }
    
    cpr::Response WebserverInterface::ping()
    {
        auto response = cpr::Get
        (
            cpr::Url{QString(Helpers::addressEndingWithSlash(settings->getWebserverAddress()) % Helpers::apiPingEndpoint()).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::versionHeaderField(),
                Helpers::apiCompetitionIdHeaderField(settings->getCompetition().getID()),
                Helpers::apiPasswordHeaderField(settings->getCompetition().getPassword())
            }
        );

        log("Web Server / Test", response);
        return response;
    }
    
    cpr::Response WebserverInterface::create(const QString& a_password)
    {
        auto response = cpr::Post
        (
            cpr::Url{QString(Helpers::addressEndingWithSlash(settings->getWebserverAddress()) % Helpers::apiCreateEndpoint()).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::versionHeaderField(),
                Helpers::jsonContentHeaderField(),
                Helpers::apiPasswordHeaderField(a_password)
            }
        );

        log("Web Server / Create New", response);
        return response;
    }
    
    cpr::Response WebserverInterface::updateMetadata()
    {
        QJsonObject json;
        json[getMetadataAlias()] = getMetadataAsBase64String();
        json[getResultsAlias()] = QString();
        
        auto response = cpr::Put
        (
            cpr::Url{QString(Helpers::addressEndingWithSlash(settings->getWebserverAddress()) % Helpers::apiUpdateMetaEndpoint()).toStdString()},
            cpr::Body{QJsonDocument{json}.toJson().toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::versionHeaderField(),
                Helpers::jsonContentHeaderField(),
                Helpers::apiCompetitionIdHeaderField(settings->getCompetition().getID()),
                Helpers::apiPasswordHeaderField(settings->getCompetition().getPassword())
            }
        );

        log("Web Server / Update Metadata", response);
        return response;
    }
    
    cpr::Response WebserverInterface::updateResults(std::vector<ResultPackage>& a_results)
    {
        QJsonObject json;
        json[getMetadataAlias()] = getMetadataAsBase64String();

        QJsonArray results_json;
        QJsonObject result_json;

        for (const auto& result : a_results)
        {
            result_json[Division::getIDAlias()] = result.division_id;
            result_json[getHtmlAlias()] = QString(result.result_file.toBase64());
            results_json.push_back(result_json);
        }

        json[getResultsAlias()] = results_json;

        auto response = cpr::Put
        (
            cpr::Url{QString(Helpers::addressEndingWithSlash(settings->getWebserverAddress()) % Helpers::apiUpdateResultsEndpoint()).toStdString()},
            cpr::Body{QJsonDocument{json}.toJson().toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::versionHeaderField(),
                Helpers::jsonContentHeaderField(),
                Helpers::apiCompetitionIdHeaderField(settings->getCompetition().getID()),
                Helpers::apiPasswordHeaderField(settings->getCompetition().getPassword())
            }
        );
        
        log("Web Server / Update Results", response);
        return response;
    }
    
    cpr::Response WebserverInterface::deleteResults()
    {
        auto response = cpr::Delete
        (
            cpr::Url{QString(Helpers::addressEndingWithSlash(settings->getWebserverAddress()) % Helpers::apiDeleteResultsEndpoint()).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::versionHeaderField(),
                Helpers::apiCompetitionIdHeaderField(settings->getCompetition().getID()),
                Helpers::apiPasswordHeaderField(settings->getCompetition().getPassword())
            }
        );
        
        log("Web Server / Delete Results", response);
        return response;
    }
    
    cpr::Response WebserverInterface::fetchAnalytics()
    {
        auto response = cpr::Get
        (
            cpr::Url{QString(
                Helpers::addressEndingWithSlash(settings->getWebserverAddress())
                % Helpers::apiAnalyticsEndpoint(settings->getCompetition().getID())).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::versionHeaderField(),
            }
        );

        log("Web Server / Fetch Analytics", response);
        return response;
    }
    
    const QString WebserverInterface::getMetadataAsBase64String() const
    {
        QJsonDocument metadata_json_doc{settings->getMetadataAsJson()};
        return QString(metadata_json_doc.toJson().toBase64());
    }
}