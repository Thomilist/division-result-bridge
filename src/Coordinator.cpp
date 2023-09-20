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
        , webserver(&settings_cache)
    { }
    
    Coordinator::~Coordinator()
    { }
    
    void Coordinator::pingWebserver()
    {
        updateCache();
        emit log("Test", webserver.ping());
        return;
    }
    
    void Coordinator::createCompetition(const QString& a_password)
    {
        updateCache();
        
        auto response = webserver.create(a_password);
        emit log("Create New", response);

        if (response.status_code != 201)
        {
            return;
        }

        auto competition_json_raw = QString::fromStdString(response.text);
        auto competition_bytes = competition_json_raw.toUtf8();
        auto competition_jsondoc = QJsonDocument::fromJson(competition_bytes);

        if (competition_jsondoc.isNull())
        {
            emit log("Create", 0, "JSON parse error", "An error occured while parsing the JSON representation of the returned competition.");
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
        emit log("Update Metadata", webserver.updateMetadata());
        return;
    }
    
    void Coordinator::updateResults()
    {
        updateCache();
        results.clear();
        
        if (meos.updateResults())
        {
            return;
        }
        
        for (const auto& division : settings_cache.getDivisions())
        {
            if (!division.isFullyDefined())
            {
                emit log(
                    "Internal",
                    0,
                    "Division Skipped",
                    QString() % "Division [" % QString::number(division.getID()) % "] is not fully defined.");
                continue;
            }

            if (calculateDivisionResults(division))
            {
                emit log(
                    Helpers::divisionsmatchberegningExeName(),
                    0,
                    "Results Calculation Error",
                    QString() % "An error occured while calculating results for division [" % QString::number(division.getID()) % "].");
                continue;
            }

            if (loadResultFile(division))
            {
                emit log(
                    "Internal",
                    0,
                    "Results Loading Error",
                    QString() % "Unable to load result file for division [" % QString::number(division.getID()) % "].");
                continue;
            }
        }

        emit log("Update Results", webserver.updateResults(results));

        return;
    }
    
    void Coordinator::updateCache()
    {
        settings_cache = *settings;
        return;
    }
    
    int Coordinator::calculateDivisionResults(const Division& a_division)
    {
        return QProcess::execute
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
            << settings_cache.getDivisionResultPath()
            // Output format
            << "-f"
            << "WWW"
        );
    }
    
    int Coordinator::loadResultFile(const Division& a_division)
    {
        QFile result_file{settings_cache.getDivisionResultPath()};

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
                    trimmed_results.append(line);
                }
            }
            
            results.push_back({a_division.getID(), trimmed_results.toUtf8()});
            return 0;
        }

        return 1;
    }
}