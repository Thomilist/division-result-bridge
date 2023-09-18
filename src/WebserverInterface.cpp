#include "WebserverInterface.hpp"


namespace divi
{
    WebserverInterface::WebserverInterface(Settings* a_settings, QObject* a_parent)
        : QObject(a_parent)
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
        return cpr::Get
        (
            cpr::Url{QString(Helpers::addressEndingWithSlash(settings->getWebserverAddress()) % Helpers::apiPingEndpoint()).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::apiCompetitionIdHeaderField(settings->getCompetition().getID()),
                Helpers::apiPasswordHeaderField(settings->getCompetition().getPassword())
            }
        );
    }
    
    cpr::Response WebserverInterface::create(const QString& a_password)
    {
        return cpr::Post
        (
            cpr::Url{QString(Helpers::addressEndingWithSlash(settings->getWebserverAddress()) % Helpers::apiCreateEndpoint()).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::jsonContentHeaderField(),
                Helpers::apiPasswordHeaderField(a_password)
            }
        );
    }
    
    cpr::Response WebserverInterface::updateMetadata()
    {
        QJsonObject json;
        json[getMetadataAlias()] = getMetadataAsBase64String();
        json[getResultsAlias()] = QString();
        
        return cpr::Put
        (
            cpr::Url{QString(Helpers::addressEndingWithSlash(settings->getWebserverAddress()) % Helpers::apiUpdateMetaEndpoint()).toStdString()},
            cpr::Body{QJsonDocument{json}.toJson().toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::jsonContentHeaderField(),
                Helpers::apiCompetitionIdHeaderField(settings->getCompetition().getID()),
                Helpers::apiPasswordHeaderField(settings->getCompetition().getPassword())
            }
        );
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

        return cpr::Put
        (
            cpr::Url{QString(Helpers::addressEndingWithSlash(settings->getWebserverAddress()) % Helpers::apiUpdateResultsEndpoint()).toStdString()},
            cpr::Body{QJsonDocument{json}.toJson().toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::jsonContentHeaderField(),
                Helpers::apiCompetitionIdHeaderField(settings->getCompetition().getID()),
                Helpers::apiPasswordHeaderField(settings->getCompetition().getPassword())
            }
        );
    }
    
    const QString WebserverInterface::getMetadataAsBase64String() const
    {
        QJsonDocument metadata_json_doc{settings->getMetadataAsJson()};
        return QString(metadata_json_doc.toJson().toBase64());
    }

}