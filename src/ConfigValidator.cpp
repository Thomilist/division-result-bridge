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

        for (const auto& division : settings->getDivisions())
        {
            if (!division.hasValidConfigPath())
            {
                emit log(MessageType::Warning, "Internal / Import Config", 0, "Invalid Path",
                    QString()
                    % "The path \""
                    % division.getDivisionConfigPath()
                    % "\" was not found (used by division with ID ["
                    % QString::number(division.getID())
                    % "])");
                
                valid = false;
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
            emit log(MessageType::Warning, "Internal / Import Config", 0, "Invalid Path",
                QString()
                % "The path \""
                % settings->getWorkingDir()
                % "\" was not found (used as working directory)");
            
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
            emit log(MessageType::Warning, "Internal / Import Config", 0, "Invalid Path",
                QString()
                % "The path \""
                % settings->getDiviExePath()
                % "\" was not found (path to \""
                % Helpers::divisionsmatchberegningExeName()
                % "\")");
            
            valid = false;
        }

        return valid;
    }
}