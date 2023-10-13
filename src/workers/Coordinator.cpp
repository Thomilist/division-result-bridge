#include "Coordinator.hpp"


namespace divi
{
    Coordinator::Coordinator(
        QObject* a_parent)
        : QObject(a_parent)
        , Loggable(Helpers::loggableCoordinator())
        , meos(&settings_cache)
        , divisionsmatch(&settings_cache)
        , webserver(&settings_cache)
    {
        attachLogging(Helpers::loggerFile());
        attachLogging(Helpers::loggerMain());
    }
    
    Coordinator::~Coordinator()
    { }
    
    void Coordinator::updateCache(Settings a_settings)
    {
        settings_cache = a_settings;
        return;
    }
    
    void Coordinator::pingWebserver()
    {
        webserver.ping();
        return;
    }
    
    void Coordinator::createCompetition(const Settings& a_request_settings)
    {
        settings_cache = a_request_settings;

        // Error or not, competitionCreated(settings_cache) should be emitted
        // Immediately invoked lambda is only used to avoid code duplication at every return
        bool success = [&] -> bool
        {
            auto response = webserver.create();

            if (response.status_code != 201)
            {
                return false;
            }

            auto competition_json_raw = QString::fromStdString(response.text);
            auto competition_bytes = competition_json_raw.toUtf8();
            auto competition_jsondoc = QJsonDocument::fromJson(competition_bytes);

            if (competition_jsondoc.isNull())
            {
                log(
                    MessageType::Error,
                    "Internal / Create New", 0, "JSON parse error",
                    "An error occured while parsing the JSON representation of the returned competition");
                return false;
            }

            auto competition_json = competition_jsondoc.object();
            settings_cache.getCompetition() = Competition::fromJson(competition_json);
            return true;
        }();

        emit competitionCreated(success ? std::optional<Settings>{settings_cache} : std::nullopt);
        return;
    }
    
    void Coordinator::updateMetadata()
    {
        webserver.updateMetadata();
        return;
    }
    
    void Coordinator::updateResults(bool a_fresh_start)
    {
        #ifdef Q_OS_WIN
        QNtfsPermissionCheckGuard ntfs_permissions;
        #endif
        
        prepareWorkingDir();

        switch (settings_cache.getResultSource())
        {
            case ResultSource::MeosDivi:
            {
                updateWithMeosDivi(a_fresh_start);
                break;
            }
            case ResultSource::Divi:
            {
                updateWithDivi();
                break;
            }
            case ResultSource::XmlDivi:
            {
                updateWithXmlDivi();
                break;
            }
            default:
            {
                log(MessageType::Error, "Internal / Update Results", 0, "Invalid Result Source",
                    QString()
                    % "The result source is set to \""
                    % Helpers::resultSource(settings_cache.getResultSource())
                    % "\", which is not valid");
                break;
            }
        }

        emit activelyProcessing(false);
        return;
    }
    
    void Coordinator::deleteResults()
    {
        webserver.deleteResults();
        return;
    }
    
    void Coordinator::fetchAnalytics()
    {
        webserver.fetchAnalytics();
        return;
    }
    
    void Coordinator::pingMeos()
    {
        meos.ping();
        return;
    }
    
    void Coordinator::fetchMetadataFromMeos()
    {
        auto competition = meos.fetchMetadata();

        if (competition.has_value())
        {
            emit metadataFetched(competition.value());
        }

        return;
    }
    
    void Coordinator::updateWithMeosDivi(bool a_fresh_start)
    {
        if (a_fresh_start)
        {
            meos.resetDifference();
        }
        
        if (meos.updateResults())
        {
            return;
        }

        auto results = divisionsmatch.loadResults();

        if (!divisionResultsValid(results))
        {
            meos.resetDifference();
            return;
        }

        auto response = webserver.updateResults(results);

        if (response.status_code != 200)
        {
            meos.resetDifference();
        }

        return;
    }
    
    void Coordinator::updateWithDivi()
    {
        auto results = divisionsmatch.loadResults();

        if (!divisionResultsValid(results))
        {
            return;
        }

        auto response = webserver.updateResults(results);

        return;
    }
    
    void Coordinator::updateWithXmlDivi()
    {
        // This should be run after the IOF XML results file has been changed.
        // DivisionInterface handles switching between result sources automatically,
        // so since nothing else (e.g. MeOS) needs to run first,
        // a separate implementation here is not required
        updateWithDivi();
        return;
    }
    
    void Coordinator::prepareWorkingDir()
    {
        QDir working_dir{settings_cache.getWorkingDir()};

        if (!working_dir.exists())
        {
            working_dir.mkpath(".");
        }

        return;
    }
    
    bool Coordinator::divisionResultsValid(const std::vector<ResultPackage>* a_results)
    {
        if (a_results == nullptr)
        {
            return false;
        }
        else if (a_results->empty())
        {
            log(MessageType::Error, "Internal / Update Results", 0, "Results Error",
                "No results to upload"
            );

            return false;
        }

        return true;
    }
}