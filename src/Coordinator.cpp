#include "Coordinator.hpp"


namespace divi
{
    Coordinator::Coordinator(
        Settings* a_settings,
        Logger* a_log,
        QObject* a_parent)
        : Loggable(a_log, a_parent)
        , settings(a_settings)
        , meos(&settings_cache, a_log)
        , webserver(a_log, &settings_cache)
    { }
    
    Coordinator::~Coordinator()
    { }
    
    void Coordinator::pingWebserver()
    {
        updateCache();
        webserver.ping();
        return;
    }
    
    void Coordinator::createCompetition(const QString& a_password)
    {
        updateCache();
        
        auto response = webserver.create(a_password);

        if (response.status_code != 201)
        {
            return;
        }

        auto competition_json_raw = QString::fromStdString(response.text);
        auto competition_bytes = competition_json_raw.toUtf8();
        auto competition_jsondoc = QJsonDocument::fromJson(competition_bytes);

        if (competition_jsondoc.isNull())
        {
            emit log(
                MessageType::Error,
                "Internal / Create New", 0, "JSON parse error",
                "An error occured while parsing the JSON representation of the returned competition");
            return;
        }

        auto competition_json = competition_jsondoc.object();
        auto competition = Competition::fromJson(competition_json);

        emit competitionCreated(competition);
        return;
    }
    
    void Coordinator::updateMetadata()
    {
        updateCache();
        webserver.updateMetadata();
        return;
    }
    
    void Coordinator::updateResults()
    {
        emit activelyProcessing(true);
        
        updateCache();
        prepareWorkingDir();
        results.clear();

        runUpdatePipeline();

        emit activelyProcessing(false);
        return;
    }
    
    void Coordinator::startFresh()
    {
        meos.resetDifference();
        return;
    }
    
    void Coordinator::runUpdatePipeline()
    {
        if (meos.updateResults())
        {
            return;
        }

        if (!diviExeExists())
        {
            return;
        }
        
        for (const auto& division : settings_cache.getDivisions())
        {
            if (!division.isFullyDefined())
            {
                emit log(
                    MessageType::Error,
                    "Internal / Update Results", 0, "Misconfigured Division",
                    QString()
                    % "Division ["
                    % QString::number(division.getID())
                    % "] is not fully defined");
                return;
            }
            
            if (!division.hasValidConfigPath())
            {
                emit log(
                    MessageType::Error,
                    "Internal / Update Results", 0, "Misconfigured Division",
                    QString()
                    % "Division ["
                    % QString::number(division.getID())
                    % "] not valid: "
                    % "\""
                    % division.getDivisionConfigPath()
                    % "\""
                    % " not found");
                
                return;
            }

            if (calculateDivisionResults(division))
            {
                emit log(
                    MessageType::Error,
                    Helpers::divisionsmatchberegningExeName() % " / Update Results", 0, "Results Calculation Error",
                    QString()
                    % "An error occured while calculating results for division ["
                    % QString::number(division.getID())
                    % "]");
                return;
            }

            if (loadResultFile(division))
            {
                emit log(
                    MessageType::Error, 
                    "Internal / Update Results", 0, "Results Loading Error",
                    QString()
                    % "Unable to load result file for division ["
                    % QString::number(division.getID())
                    % "]");
                return;
            }

            emit log(
                MessageType::Success,
                "Internal / Update Results", 0, "Results Calculation Success",
                QString()
                % "Results for division ["
                % QString::number(division.getID())
                % "] calculated and loaded");
        }

        if (results.empty())
        {
            emit log(
                MessageType::Error,
                "Internal / Update Results", 0, "Results Calculation Error",
                "No results to upload"
            );

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
    
    void Coordinator::updateCache()
    {
        settings_cache = *settings;
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
    
    int Coordinator::calculateDivisionResults(const Division& a_division)
    {
        divi_process.start
        (
            // Divisionsmatch.exe executable
            settings_cache.getDiviExePath(),

            QStringList()
            // Division configuration file
            << "-d"
            << a_division.getDivisionConfigPath()
            // IOF XML results file
            << "-c"
            << settings_cache.getXMLResultPath()
            // HTML export file
            << "-e"
            << settings_cache.getDivisionResultPath(a_division.getID())
            // Output format
            << "-f"
            << "WWW"
        );

        divi_process.waitForFinished();
        
        if (divi_process.exitCode())
        {
            emit log(MessageType::Error, Helpers::divisionsmatchberegningExeName() % " / Update Results", divi_process.exitCode(), "Process Output",
                QString::fromUtf8(divi_process.readAllStandardError()));
        }
        
        return divi_process.exitCode();
    }
    
    int Coordinator::loadResultFile(const Division& a_division)
    {
        QFile result_file{settings_cache.getDivisionResultPath(a_division.getID())};

        if (result_file.open(QIODevice::ReadOnly))
        {
            // Only include contents of <body>
            QString trimmed_results;
            QString line;
            QTextStream result_stream{&result_file};
            bool include = false;

            while (!result_stream.atEnd())
            {
                line = result_stream.readLine();

                if (line == "<body>")
                {
                    include = true;
                    continue;
                }
                else if (line == "</body></html>")
                {
                    include = false;
                    break;
                }

                if (include)
                {
                    for (const auto& item : substitutions)
                    {
                        line.replace(item.first, item.second);
                    }
                    
                    trimmed_results.append(line);
                }
            }
            
            results.push_back({a_division.getID(), trimmed_results.toUtf8()});
            return 0;
        }

        return 1;
    }
    
    bool Coordinator::diviExeExists()
    {
        QFileInfo divi_exe_info{settings->getDiviExePath()};
        bool exists = divi_exe_info.exists();

        if (!exists)
        {
            emit log(
                MessageType::Error,
                "Internal / Update Results", 0, "Invalid Path",
                QString()
                % "\""
                % settings->getDiviExePath()
                % "\""
                % " not found"
            );

            meos.resetDifference();
        }

        return exists;
    }
}