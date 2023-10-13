#include "PersistentSettings.hpp"


namespace divi
{
    PersistentSettings::PersistentSettings(QMainWindow* a_main_window)
        : QSettings(a_main_window)
        , Loggable("loggable:persistent_settings")
        , main_window(a_main_window)
    {
        attachLogging(Helpers::loggerFile());
        attachLogging(Helpers::loggerMain());
        
        loadFromRegistry();
    }
    
    PersistentSettings::~PersistentSettings()
    {
        setFirstTime(false);
        saveToRegistry();
    }
    
    const QString PersistentSettings::getConfigMetadataAlias()
    {
        return "meta";
    }
    
    const QString PersistentSettings::getConfigSourceAlias()
    {
        return "source";
    }
    
    const QString PersistentSettings::getConfigVersionAlias()
    {
        return "version";
    }
    
    // Returns:
    // 0 on success
    // 1 on empty path
    // 2 on file IO error
    // 3 on JSON error
    // 4 on invalid metadata
    int PersistentSettings::importConfig(const QString& a_path)
    {
        setExternalConfigPath(a_path);
        int error = loadFromConfig();

        switch (error)
        {
            case 0:
            {
                log(MessageType::Success, "Internal / Import Config", 0, "Import Successful",
                    QString()
                    % "Successfully imported configuration from \""
                    % a_path
                    % "\"");
                break;
            }
            case 1:
            {
                log(MessageType::Error, "Internal / Import Config", 0, "Import Failed",
                    "The import path was empty - how did that happen?");
                break;
            }
            case 2:
            {
                log(MessageType::Error, "Internal / Import Config", 0, "Import Failed",
                    QString()
                    % "Unable to read configuration file at \""
                    % a_path
                    % "\"");
                break;
            }
            case 3:
            {
                log(MessageType::Error, "Internal / Import Config", 0, "Import Failed",
                    QString()
                    % "An error occured while parsing JSON from configuration file at \""
                    % a_path
                    % "\"");
                break;
            }
            default:
            {
                break;
            }
        }

        return error;
    }
    
    // Returns:
    // 0 on success
    // 1 on empty path
    // 2 on file IO error
    int PersistentSettings::exportConfig(const QString& a_path)
    {
        setExternalConfigPath(a_path);
        int error = saveToConfig();

        switch (error)
        {
            case 0:
            {
                log(MessageType::Success, "Internal / Export Config", 0, "Export Successful",
                    QString()
                    % "Successfully exported configuration to \""
                    % a_path
                    % "\"");
                break;
            }
            case 1:
            {
                log(MessageType::Error, "Internal / Export Config", 0, "Export Failed",
                    "The export path was empty - how did that happen?");
                break;
            }
            case 2:
            {
                log(MessageType::Error, "Internal / Export Config", 0, "Export Failed",
                    QString()
                    % "Unable to write configuration file at \""
                    % a_path
                    % "\"");
                break;
            }
            default:
            {
                break;
            }
        }

        return error;
    }
    
    void PersistentSettings::loadFromRegistry()
    {
        Settings default_settings;
        
        // Main window dimensions and position
        const QByteArray geometry = value(getWindowGeometryAlias(), QByteArray()).toByteArray();

        if (!geometry.isEmpty())
        {
            main_window->restoreGeometry(geometry);
        }

        // Competition
        beginGroup(getCompetitionAlias());

        const auto& default_competition = default_settings.getCompetition();
        auto& competition_settings = getCompetition();

        competition_settings.setID(value(Competition::getIDAlias(), default_competition.getID()).toInt());
        competition_settings.setPassword(value(Competition::getPasswordAlias(), default_competition.getPassword()).toString());
        competition_settings.setName(value(Competition::getNameAlias(), default_competition.getName()).toString());
        competition_settings.setOrganiser(value(Competition::getOrganiserAlias(), default_competition.getOrganiser()).toString());
        competition_settings.setDate(value(Competition::getDateAlias(), default_competition.getDate()).toString());
        competition_settings.setTimeZone(value(Competition::getTimeZoneAlias(), default_competition.getTimeZone()).toString());
        competition_settings.setVisibility(value(Competition::getVisibilityAlias(), default_competition.getVisibility()).toString());
        competition_settings.setLiveresultsID(value(Competition::getLiveresultsIDAlias(), default_competition.getLiveresultsID()).toInt());

        endGroup();

        // General settings
        setFirstTime(value(getFirstTimeAlias(), default_settings.isFirstTime()).toBool());
        setResultSource(Helpers::resultSource(value(getResultSourceAlias(), Helpers::resultSource(default_settings.getResultSource())).toString()));
        setExternalConfigPath(value(getExternalConfigPathAlias(), default_settings.getExternalConfigPath()).toString());
        setWorkingDir(value(getWorkingDirAlias(), default_settings.getWorkingDir()).toString());
        setDiviExePath(value(getDiviExePathAlias(), default_settings.getDiviExePath()).toString());
        setXmlResultPath(value(getXmlResultPathAlias(), default_settings.getXmlResultPath()).toString());
        setMeosAddress(value(getMeosAddressAlias(), default_settings.getMeosAddress()).toString());
        setWebserverAddress(value(getWebserverAddressAlias(), default_settings.getWebserverAddress()).toString());
        setUpdateInterval(value(getUpdateIntervalAlias(), default_settings.getUpdateInterval()).toInt());
        setPrettyLogging(value(getPrettyLoggingAlias(), default_settings.getPrettyLogging()).toBool());
        setRawLogging(value(getRawLoggingAlias(), default_settings.getRawLogging()).toBool());

        // Divisions
        int size = beginReadArray(getDivisionsAlias());
        divisions.clear();

        Division default_division;

        for (int index = 0; index < size; ++index)
        {
            setArrayIndex(index);
            divisions.push_back(Division(
                value(Division::getIDAlias(), default_division.getID()).toInt(),
                value(Division::getNameAlias(), default_division.getName()).toString(),
                value(Division::getConfigPathAlias(), default_division.getConfigPath()).toString(),
                value(Division::getInfoServerAddressAlias(), default_division.getInfoServerAddress()).toString()
            ));
        }

        endArray();

        return;
    }
    
    void PersistentSettings::saveToRegistry()
    {
        // Main window dimensions and position
        setValue(getWindowGeometryAlias(), main_window->saveGeometry());

        // Competition
        beginGroup(getCompetitionAlias());

        const auto& competition_settings = getCompetition();

        setValue(Competition::getIDAlias(), competition_settings.getID());
        setValue(Competition::getPasswordAlias(), competition_settings.getPassword());
        setValue(Competition::getNameAlias(), competition_settings.getName());
        setValue(Competition::getOrganiserAlias(), competition_settings.getOrganiser());
        setValue(Competition::getDateAlias(), competition_settings.getDate());
        setValue(Competition::getTimeZoneAlias(), competition_settings.getTimeZone());
        setValue(Competition::getVisibilityAlias(), competition_settings.getVisibility());
        setValue(Competition::getLiveresultsIDAlias(), competition_settings.getLiveresultsID());

        endGroup();

        // General settings
        setValue(getFirstTimeAlias(), isFirstTime());
        setValue(getResultSourceAlias(), Helpers::resultSource(getResultSource()));
        setValue(getExternalConfigPathAlias(), getExternalConfigPath());
        setValue(getWorkingDirAlias(), getWorkingDir());
        setValue(getDiviExePathAlias(), getDiviExePath());
        setValue(getXmlResultPathAlias(), getXmlResultPath());
        setValue(getMeosAddressAlias(), getMeosAddress());
        setValue(getWebserverAddressAlias(), getWebserverAddress());
        setValue(getUpdateIntervalAlias(), getUpdateInterval());
        setValue(getPrettyLoggingAlias(), getPrettyLogging());
        setValue(getRawLoggingAlias(), getRawLogging());

        // Divisions
        beginWriteArray(getDivisionsAlias());

        int index = 0;

        for (const auto& division : getDivisions())
        {
            setArrayIndex(index++);
            setValue(Division::getIDAlias(), division.getID());
            setValue(Division::getNameAlias(), division.getName());
            setValue(Division::getConfigPathAlias(), division.getConfigPath());
            setValue(Division::getInfoServerAddressAlias(), division.getInfoServerAddress());
        }

        endArray();

        return;
    }
    
    // Returns:
    // 0 on success
    // 1 on empty path
    // 2 on file IO error
    // 3 on JSON error
    // 4 on invalid metadata
    int PersistentSettings::loadFromConfig()
    {
        if (external_config_path.isEmpty())
        {
            return 1;
        }

        QFile json_file{external_config_path};

        if (json_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonDocument json_doc = QJsonDocument::fromJson(json_file.readAll());

            if (json_doc.isNull())
            {
                return 3;
            }

            QJsonObject json = json_doc.object();

            if (!isLoadedConfigValid(json))
            {
                return 4;
            }

            if (const QJsonValue value = json[getResultSourceAlias()]; value.isString())
            {
                setResultSource(value.toString());
            }

            if (const QJsonValue value = json[getCompetitionAlias()]; value.isObject())
            {
                QJsonObject competition_json = value.toObject();
                competition = Competition::fromJson(competition_json);
            }

            if (const QJsonValue value = json[getWorkingDirAlias()]; value.isString())
            {
                setWorkingDir(value.toString());
            }

            if (const QJsonValue value = json[getDiviExePathAlias()]; value.isString())
            {
                setDiviExePath(value.toString());
            }

            if (const QJsonValue value = json[getXmlResultPath()]; value.isString())
            {
                setXmlResultPath(value.toString());
            }

            if (const QJsonValue value = json[getMeosAddressAlias()]; value.isString())
            {
                setMeosAddress(value.toString());
            }

            if (const QJsonValue value = json[getWebserverAddressAlias()]; value.isString())
            {
                setWebserverAddress(value.toString());
            }

            if (const QJsonValue value = json[getUpdateIntervalAlias()]; value.isDouble())
            {
                setUpdateInterval(value.toInt());
            }

            if (const QJsonValue value = json[getDivisionsAlias()]; value.isArray())
            {
                emit clearDivisions();
                QJsonArray divisions_json = value.toArray();

                for (const QJsonValue& division : divisions_json)
                {
                    if (division.isObject())
                    {
                        emit addDivision(Division::fromJson(division.toObject()));
                    }
                }
            }
        }
        else
        {
            return 2;
        }

        return 0;
    }
    
    // Returns:
    // 0 on success
    // 1 on empty path
    // 2 on file IO error
    int PersistentSettings::saveToConfig()
    {
        if (external_config_path.isEmpty())
        {
            return 1;
        }

        QJsonObject json;
        QJsonObject meta_json;
        QJsonArray divisions_json;
        QJsonObject competition_json = getCompetition().toJson();

        meta_json[getConfigSourceAlias()] = Helpers::projectName();
        meta_json[getConfigVersionAlias()] = Helpers::projectVersion();
        json[getConfigMetadataAlias()] = meta_json;
        
        for (const Division& division : getDivisions())
        {
            divisions_json.push_back(division.toJson());
        }

        json[getResultSourceAlias()] = Helpers::resultSource(getResultSource());
        json[getCompetitionAlias()] = competition_json;
        json[getWorkingDirAlias()] = getWorkingDir();
        json[getDiviExePathAlias()] = getDiviExePath();
        json[getXmlResultPathAlias()] = getXmlResultPath();
        json[getMeosAddressAlias()] = getMeosAddress();
        json[getWebserverAddressAlias()] = getWebserverAddress();
        json[getUpdateIntervalAlias()] = getUpdateInterval();
        json[getDivisionsAlias()] = divisions_json;

        QJsonDocument json_doc{json};
        QFile config_file{external_config_path};

        if (config_file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream json_output{&config_file};
            json_output << json_doc.toJson();
        }
        else
        {
            return 2;
        }

        return 0;
    }
    
    bool PersistentSettings::isLoadedConfigValid(const QJsonObject& a_config_json)
    {
        QString source;
        QString version_tag;
        
        if (const QJsonValue value = a_config_json[getConfigMetadataAlias()]; value.isObject())
        {
            QJsonObject metadata_json = value.toObject();

            if (const QJsonValue value = metadata_json[getConfigSourceAlias()]; value.isString())
            {
                source = value.toString();
            }

            if (const QJsonValue value = metadata_json[getConfigVersionAlias()]; value.isString())
            {
                version_tag = value.toString();
            }
        }

        if (source.isEmpty())
        {
            log(MessageType::Error, "Internal / Import Config", 0, "Invalid Config",
                QString()
                % getConfigMetadataAlias()
                % "."
                % getConfigSourceAlias()
                % " is undefined");
            
            return false;
        }

        if (source != Helpers::projectName())
        {
            log(MessageType::Error, "Internal / Import Config", 0, "Invalid Config",
                QString()
                % getConfigMetadataAlias()
                % "."
                % getConfigSourceAlias()
                % " is \""
                % source
                % "\" (expected \""
                % Helpers::projectName()
                % "\")");
            
            return false;
        }

        auto version_comparison = Version::compare(Helpers::projectVersion(), version_tag);

        if (version_comparison == VersionComparison::_Undefined)
        {
            log(MessageType::Warning, "Internal / Import Config", 0, "_Undefined Config Version",
                QString()
                % getConfigMetadataAlias()
                % "."
                % getConfigVersionAlias()
                % " is undefined");
        }
        else if (std::ranges::contains(std::array{
            VersionComparison::OlderMajor,
            VersionComparison::OlderMinor,
            VersionComparison::OlderPatch}
            , version_comparison))
        {
            log(MessageType::Warning, "Internal / Import Config", 0, "Old Config Version",
                QString()
                % "The imported config file is from version "
                % version_tag
                % ", but the current version is "
                % Helpers::projectVersion()
                % ". "
                % (version_comparison == VersionComparison::OlderMajor
                    ? "There may be breaking changes between these versions, so proceed with care"
                    : "This should be okay, but check the imported values to be sure"));
        }

        return true;
    }
}