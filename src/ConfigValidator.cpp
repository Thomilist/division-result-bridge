#include "ConfigValidator.hpp"


namespace divi
{
    ConfigValidator::ConfigValidator(
        Logger* a_log,
        Settings* a_settings,
        QObject* a_parent)
        : Loggable(a_log, a_parent)
        , settings(a_settings)
    { }
    
    ConfigValidator::~ConfigValidator()
    { }
    
    bool ConfigValidator::validate()
    {
        bool valid = true;

        valid &= divisionPathsValid();
        valid &= workingDirValid();
        valid &= diviExePathValid();

        return valid;
    }
    
    bool ConfigValidator::divisionPathsValid()
    {
        bool valid = true;
        std::unordered_map<QString, std::set<int>> config_uses;

        for (const auto& division : settings->getDivisions())
        {
            if (!division.hasValidConfigPath())
            {
                log(MessageType::Warning, "Internal / Load Config", 0, "Invalid Path",
                    QString()
                    % "The path \""
                    % division.getDivisionConfigPath()
                    % "\" was not found (used by division with ID ["
                    % QString::number(division.getID())
                    % "])");
                
                valid = false;
            }

            // Track which IDs a path is used with
            if (const QString path = division.getDivisionConfigPath(); !path.isEmpty())
            {
                if (config_uses.contains(path))
                {
                    config_uses.at(path).insert(division.getID());
                }
                else
                {
                    config_uses.insert({path, {division.getID()}});
                }
            }
        }

        // Warn when a path is used for multiple IDs
        for (const auto& config_use : config_uses)
        {
            if (config_use.second.size() > 1)
            {
                QStringList division_ids;

                for (const auto& id : config_use.second)
                {
                    division_ids.push_back("[" % QString::number(id) % "]");
                }

                log(MessageType::Warning, "Internal / Load Config", 0, "Duplicate Division Config Use",
                    QString()
                    % "The division configuration at path \""
                    % config_use.first
                    % "\" is used in "
                    % QString::number(config_use.second.size())
                    % " divisions, these being IDs "
                    % division_ids.join(", "));
            }
        }

        return valid;
    }
    
    bool ConfigValidator::workingDirValid()
    {
        bool valid = true;
        QDir working_dir{settings->getWorkingDir()};

        if (!working_dir.exists())
        {
            log(MessageType::Warning, "Internal / Load Config", 0, "Invalid Path",
                QString()
                % "The path \""
                % settings->getWorkingDir()
                % "\" was not found (used as working directory)");
            
            valid = false;
        }
        else if (settings->getWorkingDir().isEmpty())
        {
            log(MessageType::Warning, "Internal / Load Config", 0, "Invalid Path",
                QString()
                % "The working directory path is empty");
            
            valid = false;
        }

        return valid;
    }
    
    bool ConfigValidator::diviExePathValid()
    {
        bool valid = true;
        QFileInfo divi_exe_path{settings->getDiviExePath()};

        if (!divi_exe_path.exists())
        {
            log(MessageType::Warning, "Internal / Load Config", 0, "Invalid Path",
                QString()
                % "\""
                % Helpers::divisionsmatchberegningExeName()
                % "\" was not found on the path \""
                % settings->getDiviExePath()
                % "\"");
            
            valid = false;
        }

        return valid;
    }
}