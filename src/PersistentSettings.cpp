#include "PersistentSettings.hpp"


namespace divi
{
    PersistentSettings::PersistentSettings(QMainWindow* a_main_window, Logger* a_log)
        : QSettings(a_main_window)
        , Loggable(a_log, this)
        , Settings(a_main_window)
    {
        loadFromRegistry();
    }
    
    PersistentSettings::~PersistentSettings()
    {
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
    
    void PersistentSettings::importConfig(const QString& a_path)
    {
        setExternalConfigPath(a_path);
        loadFromConfig();
        return;
    }
    
    void PersistentSettings::exportConfig(const QString& a_path)
    {
        setExternalConfigPath(a_path);
        saveToConfig();
        return;
    }
    
    void PersistentSettings::loadFromRegistry()
    {
        // Main window dimensions and position
        const QByteArray geometry = value(getWindowGeometryAlias(), QByteArray()).toByteArray();

        if (!geometry.isEmpty())
        {
            main_window->restoreGeometry(geometry);
        }

        // Competition
        beginGroup(getCompetitionAlias());

        competition.setID(value(Competition::getIDAlias(), 0).toInt());
        competition.setPassword(value(Competition::getPasswordAlias(), "").toString());
        competition.setName(value(Competition::getNameAlias(), "").toString());
        competition.setOrganiser(value(Competition::getOrganiserAlias(), "").toString());
        competition.setDate(value(Competition::getDateAlias(), "").toString());
        competition.setVisibility(value(Competition::getVisibilityAlias(), Helpers::visibility(Visibility::PRIVATE)).toString());
        competition.setLiveresultsID(value(Competition::getLiveresultsIDAlias(), 0).toInt());

        endGroup();

        auto temp_locations = QStandardPaths::standardLocations(QStandardPaths::TempLocation);
        const QString default_working_dir = temp_locations.isEmpty() ? "" : temp_locations.front();

        // General settings
        external_config_path = value(getExternalConfigPathAlias(), "").toString();
        working_dir = value(getWorkingDirAlias(), default_working_dir).toString();
        divi_exe_path = value(getDiviExePathAlias(), "").toString();
        meos_address = value(getMeosAddressAlias(), Helpers::defaultMeosInfoServerAddress()).toString();
        webserver_address = value(getWebserverAddressAlias(), Helpers::defaultWebServerAddress()).toString();
        update_interval = value(getUpdateIntervalAlias(), 60).toInt();
        save_pretty_log = value(getPrettyLoggingAlias(), true).toBool();
        save_raw_log = value(getRawLoggingAlias(), false).toBool();

        // Divisions
        int size = beginReadArray(getDivisionsAlias());
        divisions.clear();

        for (int index = 0; index < size; ++index)
        {
            setArrayIndex(index);
            divisions.push_back(Division(
                value(Division::getIDAlias()).toInt(),
                value(Division::getDivisionConfigPathAlias()).toString(),
                value(Division::getNameAlias()).toString()
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

        setValue(Competition::getIDAlias(), competition.getID());
        setValue(Competition::getPasswordAlias(), competition.getPassword());
        setValue(Competition::getNameAlias(), competition.getName());
        setValue(Competition::getOrganiserAlias(), competition.getOrganiser());
        setValue(Competition::getDateAlias(), competition.getDate());
        setValue(Competition::getVisibilityAlias(), competition.getVisibility());
        setValue(Competition::getLiveresultsIDAlias(), competition.getLiveresultsID());

        endGroup();

        // General settings
        setValue(getExternalConfigPathAlias(), external_config_path);
        setValue(getWorkingDirAlias(), working_dir);
        setValue(getDiviExePathAlias(), divi_exe_path);
        setValue(getMeosAddressAlias(), meos_address);
        setValue(getWebserverAddressAlias(), webserver_address);
        setValue(getUpdateIntervalAlias(), update_interval);
        setValue(getPrettyLoggingAlias(), save_pretty_log);
        setValue(getRawLoggingAlias(), save_raw_log);

        // Divisions
        beginWriteArray(getDivisionsAlias());

        int index = 0;

        for (const auto& division : divisions)
        {
            setArrayIndex(index++);
            setValue(Division::getIDAlias(), division.getID());
            setValue(Division::getDivisionConfigPathAlias(), division.getDivisionConfigPath());
            setValue(Division::getNameAlias(), division.getName());
        }

        endArray();

        return;
    }
    
    void PersistentSettings::loadFromConfig()
    {
        if (external_config_path.isEmpty())
        {
            return;
        }

        QFile json_file{external_config_path};

        if (json_file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonDocument json_doc = QJsonDocument::fromJson(json_file.readAll());

            if (json_doc.isNull())
            {
                return;
            }

            QJsonObject json = json_doc.object();

            if (!isLoadedConfigValid(json))
            {
                return;
            }

            if (const QJsonValue value = json[getCompetitionAlias()]; value.isObject())
            {
                QJsonObject competition_json = value.toObject();

                if (const QJsonValue value = competition_json[Competition::getIDAlias()]; value.isDouble())
                {
                    competition.setID(value.toInt());
                }

                if (const QJsonValue value = competition_json[Competition::getPasswordAlias()]; value.isString())
                {
                    competition.setPassword(value.toString());
                }

                if (const QJsonValue value = competition_json[Competition::getNameAlias()]; value.isString())
                {
                    competition.setName(value.toString());
                }

                if (const QJsonValue value = competition_json[Competition::getOrganiserAlias()]; value.isString())
                {
                    competition.setOrganiser(value.toString());
                }

                if (const QJsonValue value = competition_json[Competition::getDateAlias()]; value.isString())
                {
                    competition.setDate(value.toString());
                }

                if (const QJsonValue value = competition_json[Competition::getVisibilityAlias()]; value.isString())
                {
                    competition.setVisibility(value.toString());
                }

                if (const QJsonValue value = competition_json[Competition::getLiveresultsIDAlias()]; value.isDouble())
                {
                    competition.setLiveresultsID(value.toInt());
                }
            }

            if (const QJsonValue value = json[getWorkingDirAlias()]; value.isString())
            {
                working_dir = value.toString();
            }

            if (const QJsonValue value = json[getDiviExePathAlias()]; value.isString())
            {
                divi_exe_path = value.toString();
            }

            if (const QJsonValue value = json[getMeosAddressAlias()]; value.isString())
            {
                meos_address = value.toString();
            }

            if (const QJsonValue value = json[getWebserverAddressAlias()]; value.isString())
            {
                webserver_address = value.toString();
            }

            if (const QJsonValue value = json[getUpdateIntervalAlias()]; value.isDouble())
            {
                update_interval = value.toInt();
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

        return;
    }
    
    void PersistentSettings::saveToConfig()
    {
        if (external_config_path.isEmpty())
        {
            return;
        }

        QJsonObject json;
        QJsonObject meta_json;
        QJsonArray divisions_json;
        QJsonObject competition_json = competition.toJson();

        meta_json[getConfigSourceAlias()] = Helpers::projectName();
        meta_json[getConfigVersionAlias()] = Helpers::projectVersion();
        json[getConfigMetadataAlias()] = meta_json;
        
        for (const Division& division : divisions)
        {
            divisions_json.push_back(division.toJson());
        }

        json[getCompetitionAlias()] = competition_json;
        json[getWorkingDirAlias()] = working_dir;
        json[getDiviExePathAlias()] = divi_exe_path;
        json[getMeosAddressAlias()] = meos_address;
        json[getWebserverAddressAlias()] = webserver_address;
        json[getUpdateIntervalAlias()] = update_interval;
        json[getDivisionsAlias()] = divisions_json;

        QJsonDocument json_doc{json};
        QFile config_file{external_config_path};

        if (config_file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream json_output{&config_file};
            json_output << json_doc.toJson();
        }

        return;
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

        if (version_comparison == VersionComparison::Undefined)
        {
            log(MessageType::Warning, "Internal / Import Config", 0, "Undefined Config Version",
                QString()
                % getConfigMetadataAlias()
                % "."
                % getConfigVersionAlias()
                % " is undefined");
        }
        else if (std::ranges::contains(std::vector{
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
                    ? "There may be breaking changes between the versions, so proceed with care"
                    : "This should be okay, but check the imported values to be sure"));
        }

        return true;
    }
}