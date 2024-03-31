#include "DivisionInterface.hpp"


namespace divi
{
    DivisionInterface::DivisionInterface(Settings* a_settings)
        : Loggable(Helpers::loggableDivisionInterface())
        , settings(a_settings)
    {
        attachLogging(Helpers::loggerFile());
        attachLogging(Helpers::loggerMain());
    }
    
    DivisionInterface::~DivisionInterface()
    { }
    
    const QString DivisionInterface::resultsHtmlEndpoint()
    {
        return "all?format=html";
    }
    
    // Returns nullptr on error
    const std::vector<ResultPackage>* DivisionInterface::loadResults()
    {
        results.clear();
        bool error = false;
        
        switch (settings->getResultSource())
        {
            case ResultSource::Divi:
            {
                error = error || useInfoServer();
                break;
            }
            case ResultSource::MeosDivi:
            case ResultSource::XmlDivi:
            {
                error = error || useCommandLine();
                break;
            }
            default:
            {
                error = true;
                break;
            }
        }
        
        if (error)
        {
            return nullptr;
        }

        return &results;
    }
    
    // Returns:
    // 0 on success
    // 1 on misconfigured division
    // 2 on result loading error
    int DivisionInterface::useInfoServer()
    {
        for (const auto& division : settings->getDivisions())
        {
            if (!isDivisionValid(division))
            {
                return 1;
            }

            if (fetchResultsFromInfoServer(division))
            {
                return 2;
            }
            
            log(MessageType::Success, "Internal / Update Results", 0, "Results Loaded",
                QString()
                % "Results for division ["
                % QString::number(division.getID())
                % "] loaded successfully");
        }
        
        return 0;
    }
    
    // Returns:
    // 0 on success
    // 1 on HTTP GET error
    // 2 on empty response body
    int DivisionInterface::fetchResultsFromInfoServer(const Division& a_division)
    {
        const QString address = a_division.getInfoServerAddress();
        
        cpr::Response response = cpr::Get
        (
            cpr::Url{QString((address.back() == '/' ? address : address % "/") % resultsHtmlEndpoint()).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                Helpers::versionHeaderField(),
                {"Accept", "text/html"}
            }
        );

        log(Helpers::diviNameShort() % " / Fetch Results", response);

        if (response.status_code != 200)
        {
            return 1;
        }

        if (response.text.empty())
        {
            log(MessageType::Error, "Internal / Fetch Results", 0, "Empty Response",
                QString()
                % Helpers::diviNameShort()
                % " successfully responded to the request, but no data was attached");
            return 2;
        }

        QString result_html = QString::fromStdString(response.text);
        QTextStream result_stream{&result_html, QIODevice::ReadOnly};

        packageResults(a_division, result_stream);
        
        return 0;
    }
    
    // Returns:
    // 0 on success
    // 1 if Divisionsmatch.exe was not found
    // 2 on misconfigured division
    // 3 on Divisionsmatch.exe runtime error
    // 4 on result loading error
    int DivisionInterface::useCommandLine()
    {
        if (!diviExeExists())
        {
            return 1;
        }

        for (const auto& division : settings->getDivisions())
        {
            if (!isDivisionValid(division))
            {
                return 2;
            }

            if (runDivisionResultCommand(division))
            {
                return 3;
            }

            if (fetchResultsFromFile(division))
            {
                return 4;
            }
            
            log(MessageType::Success, "Internal / Update Results", 0, "Results Loaded",
                QString()
                % "Results for division ["
                % QString::number(division.getID())
                % "] loaded successfully");
        }

        return 0;
    }
    
    int DivisionInterface::runDivisionResultCommand(const Division& a_division)
    {
        divi_process.start
        (
            // Divisionsmatch.exe executable
            settings->getDiviExePath(),

            QStringList()
            // Division configuration file
            << "-d"
            << a_division.getConfigPath()
            // IOF XML results file
            << "-c"
            << settings->getDynamicXmlResultPath()
            // HTML export file
            << "-e"
            << settings->getDivisionResultPath(a_division.getID())
            // Output format
            << "-f"
            << "WWW"
        );

        divi_process.waitForFinished();
        
        if (divi_process.exitCode())
        {
            log(MessageType::Error, Helpers::diviNameShort() % " / Update Results", divi_process.exitCode(), "Process Output",
                QString::fromUtf8(divi_process.readAllStandardError()));
        }
        
        return divi_process.exitCode();
    }
    
    // Returns;
    // 0 on success
    // 1 on file error
    int DivisionInterface::fetchResultsFromFile(const Division& a_division)
    {
        QFile result_file{settings->getDivisionResultPath(a_division.getID())};

        if (result_file.open(QIODevice::ReadOnly))
        {
            QTextStream result_stream{&result_file};
            packageResults(a_division, result_stream);
            return 0;
        }

        log(MessageType::Error, "Internal / Update Results", 0, "File Loading Error",
            QString()
            % "Unable to load results from file \""
            % settings->getDivisionResultPath(a_division.getID())
            % "\"");
        
        return 1;
    }
    
    bool DivisionInterface::diviExeExists()
    {
        QFileInfo divi_exe_info{settings->getDiviExePath()};
        bool exists = divi_exe_info.exists();

        if (!exists)
        {
            log(MessageType::Error, "Internal / Update Results", 0, "Invalid Path",
                QString()
                % "\""
                % settings->getDiviExePath()
                % "\""
                % " not found");
        }

        return exists;
    }
    
    bool DivisionInterface::isDivisionValid(const Division& a_division)
    {
        if (!a_division.isFullyDefined(settings->getResultSource()))
        {
            log(MessageType::Error, "Internal / Update Results", 0, "Misconfigured Division",
                QString()
                % "Division ["
                % QString::number(a_division.getID())
                % "] is not fully defined");
            return false;
        }

        switch (settings->getResultSource())
        {
            case ResultSource::MeosDivi:
            case ResultSource::XmlDivi:
            {
                if (!a_division.hasValidConfigPath())
                {
                    log(MessageType::Error, "Internal / Update Results", 0, "Misconfigured Division",
                        QString()
                        % "Division ["
                        % QString::number(a_division.getID())
                        % "] not valid: "
                        % "\""
                        % a_division.getConfigPath()
                        % "\""
                        % " not found");
                    return false;
                }
            }
            default:
            {
                break;
            }
        }

        return true;
    }
    
    // Only include HTML body and make a few string substitutions for formatting
    void DivisionInterface::packageResults(const Division& a_division, QTextStream& a_result_stream)
    {
        QString trimmed_result;
        QString line;
        bool include = false;

        while (!a_result_stream.atEnd())
        {
            line = a_result_stream.readLine();

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
                
                trimmed_result.append(line);
            }
        }

        results.push_back({a_division.getID(), trimmed_result.toUtf8()});
        return;
    }
}