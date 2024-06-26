#include "Settings.hpp"


namespace divi
{
    Settings::Settings()
    {
        const auto desktop_locations = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
        setExternalConfigPath((desktop_locations.isEmpty() ? "" : desktop_locations.front()));

        const auto temp_locations = QStandardPaths::standardLocations(QStandardPaths::TempLocation);
        setWorkingDir((temp_locations.isEmpty() ? QString() : (temp_locations.front() % "/" % Helpers::projectName())));

        setMeosAddress(Helpers::defaultMeosInfoServerAddress());
        setWebserverAddress(Helpers::defaultWebServerAddress());
    }
    
    Settings::~Settings()
    { }
    
    const QJsonObject Settings::getMetadataAsJson() const
    {
        QJsonObject json;

        QJsonObject division_json;
        QJsonArray divisions_json;

        QJsonObject competition_json = competition.toJson();

        for (const Division& division : divisions)
        {
            division_json[Division::getIDAlias()] = division.getID();
            division_json[Division::getNameAlias()] = division.getName();
            divisions_json.push_back(division_json);
        }

        json[getCompetitionAlias()] = competition_json;
        json[getDivisionsAlias()] = divisions_json;

        return json;
    }
    
    const QString Settings::getWindowGeometryAlias()
    {
        return "window_geometry";
    }
    
    void Settings::setFirstTime(bool a_state)
    {
        first_time = a_state;
        return;
    }
    
    bool Settings::isFirstTime() const
    {
        return first_time;
    }
    
    const QString Settings::getFirstTimeAlias()
    {
        return "first_time";
    }
    
    void Settings::setResultSource(const QString& a_result_source)
    {
        if (const ResultSource new_source = Helpers::resultSource(a_result_source); new_source != ResultSource::_Undefined)
        {
            result_source = new_source;
        }

        return;
    }
    
    void Settings::setResultSource(ResultSource a_result_source)
    {
        result_source = a_result_source;
        return;
    }
    
    ResultSource Settings::getResultSource() const
    {
        return result_source;
    }
    
    const QString Settings::getResultSourceAlias()
    {
        return "result_source";
    }
    
    Competition& Settings::getCompetition()
    {
        return competition;
    }
    
    const QString Settings::getCompetitionAlias()
    {
        return "competition";
    }
    
    std::vector<Division>& Settings::getDivisions()
    {
        return divisions;
    }
    
    const QString Settings::getDivisionsAlias()
    {
        return "divisions";
    }
    
    void Settings::setPrettyLogging(bool a_state)
    {
        save_pretty_log = a_state;
        return;
    }
    
    bool Settings::getPrettyLogging() const
    {
        return save_pretty_log;
    }
    
    const QString Settings::getPrettyLoggingAlias()
    {
        return "save_pretty_log";
    }
    
    void Settings::setRawLogging(bool a_state)
    {
        save_raw_log = a_state;
        return;
    }
    
    bool Settings::getRawLogging() const
    {
        return save_raw_log;
    }
    
    const QString Settings::getRawLoggingAlias()
    {
        return "save_raw_log";
    }
    
    void Settings::setExternalConfigPath(const QString& a_path)
    {
        external_config_path = a_path;
        return;
    }
    
    const QString& Settings::getExternalConfigPath() const
    {
        return external_config_path;
    }
    
    const QString Settings::getExternalConfigPathAlias()
    {
        return "external_config_path";
    }
    
    void Settings::setWorkingDir(const QString& a_dir)
    {
        working_dir = a_dir;
        return;
    }
    
    const QString& Settings::getWorkingDir() const
    {
        return working_dir;
    }
    
    const QString Settings::getWorkingDirAlias()
    {
        return "working_dir";
    }
    
    const QString Settings::getDynamicXmlResultPath()
    {
        switch (result_source)
        {
            case ResultSource::XmlDivi:
            {
                return xml_result_path;
            }
            default:
            {
                break;
            }
        }
        
        return getWorkingDir() % "/results.xml";
    }
    
    const QString Settings::getDivisionResultPath(int a_division_id)
    {
        if (a_division_id > 0)
        {
            return getWorkingDir() % "/results" % QString::number(a_division_id) % ".html";
        }
        
        return getWorkingDir() % "/results.html";
    }
    
    const QString Settings::getRawLogPath()
    {
        return getWorkingDir() % "/log.txt";
    }
    
    const QString Settings::getHtmlLogPath()
    {
        return getWorkingDir() % "/log.html";
    }
    
    void Settings::setDiviExePath(const QString& a_path)
    {
        divi_exe_path = a_path;
        return;
    }
    
    const QString& Settings::getDiviExePath() const
    {
        return divi_exe_path;
    }
    
    const QString Settings::getDiviExePathAlias()
    {
        return "divi_exe_path";
    }
    
    void Settings::setXmlResultPath(const QString& a_path)
    {
        xml_result_path = a_path;
        return;
    }
    
    const QString& Settings::getXmlResultPath() const
    {
        return xml_result_path;
    }
    
    const QString Settings::getXmlResultPathAlias()
    {
        return "xml_result_path";
    }
    
    void Settings::setMeosAddress(const QString& a_address)
    {
        meos_address = a_address;
        return;
    }
    
    const QString& Settings::getMeosAddress() const
    {
        return meos_address;
    }
    
    const QString Settings::getMeosAddressAlias()
    {
        return "meos_address";
    }
    
    void Settings::setWebserverAddress(const QString& a_address)
    {
        webserver_address = a_address;
        return;
    }
    
    const QString& Settings::getWebserverAddress() const
    {
        return webserver_address;
    }
    
    const QString Settings::getWebserverAddressAlias()
    {
        return "webserver_address";
    }
    
    void Settings::setUpdateInterval(int a_interval)
    {
        update_interval = a_interval;
        return;
    }
    
    int Settings::getUpdateInterval() const
    {
        return update_interval;
    }
    
    const QString Settings::getUpdateIntervalAlias()
    {
        return "update_interval";
    }
}